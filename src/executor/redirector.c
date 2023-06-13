/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:25:06 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/13 22:21:01 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

int	red_out(t_command *cmd, t_lexer_token *red)
{
	int	fd;

	(void)cmd;
	fd = open(red->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		mini_perr("minishell: ", red->str, 1, 0);
	return (fd);
}

int	red_append(t_command *cmd, t_lexer_token *red)
{
	int	fd;

	(void)cmd;
	fd = open(red->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		mini_perr("minishell: ", red->str, 1, 0);
	return (fd);
}

int	red_in(t_command *cmd, t_lexer_token *red)
{
	int	fd;

	(void)cmd;
	fd = open(red->str, O_RDONLY);
	if (fd == -1)
		mini_perr("minishell: ", red->str, 1, 0);
	return (fd);
}

int	redirector(t_command *commands_list)
{
	t_lexer_token	*red;
	t_command		*cmd;

	cmd = commands_list;
	while (cmd)
	{
		red = cmd->redirs;
		cmd->fd[1] = STDOUT_FILENO;
		while (red)
		{
			if (red->token_type == GREAT && set_fd(cmd, red, &red_out, 1) == -1)
				return (-1);
			if (red->token_type == G_GREAT && \
					set_fd(cmd, red, &red_append, 1) == -1)
				return (-1);
			if (red->token_type == LESS && set_fd(cmd, red, &red_in, 0) == -1)
				return (-1);
			if (red->token_type == L_LESS && \
					set_fd(cmd, red, &red_heredoc, 0) == -1)
				return (-1);
			red = red->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
