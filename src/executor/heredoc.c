/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:37:49 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/03 21:39:08 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
#include "../../includes/global.h"

static char	*create_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*filename;

	num = ft_itoa(i);
	filename = ft_strjoin(".tmp_heredoc_file_", num);
	free(num);
	return (filename);
}

int	create_heredoc(t_lexer_token *heredoc, bool quotes, t_app *app,
	char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline(HEREDOC_MSG);
	while (line && ft_strncmp(heredoc->str, line, ft_strlen(heredoc->str))
		&& !g_status.stop_heredoc)
	{
		if (quotes == false)
			line = expander_str(app, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HEREDOC_MSG);
	}
	free(line);
	if (g_status.stop_heredoc || !line)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

int	heredoc(t_app *app, t_lexer_token *heredoc, char *filename)
{
	bool	quotes;
	int		status;

	status = EXIT_SUCCESS;
	quotes = false;
	if ((heredoc->str[0] == '\"'
			&& heredoc->str[ft_strlen(heredoc->str) - 1] == '\"')
		|| (heredoc->str[0] == '\''
			&& heredoc->str[ft_strlen(heredoc->str) - 1] == '\''))
		quotes = true;
	delete_quotes(heredoc->str, '\"');
	delete_quotes(heredoc->str, '\'');
	g_status.stop_heredoc = 0;
	g_status.in_heredoc = 1;
	status = create_heredoc(heredoc, quotes, app, filename);
	g_status.in_heredoc = 0;
	app->heredoc = true;
	return (status);
}

int	send_heredoc(t_app *app, t_command *command)
{
	t_lexer_token	*token;
	int				status;

	token = command->redirs;
	status = EXIT_SUCCESS;
	while (command->redirs)
	{
		if (command->redirs->token_type == L_LESS)
		{
			if (command->heredoc)
				free(command->heredoc);
			command->heredoc = create_heredoc_filename();
			status = heredoc(app, command->redirs, command->heredoc);
			if (status)
			{
				g_status.error_num = 1;
				return (reset(app));
			}
		}
		command->redirs = command->redirs->next;
	}
	command->redirs = token;
	return (EXIT_SUCCESS);
}
