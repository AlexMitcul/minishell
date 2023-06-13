/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 22:20:09 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/13 22:22:46 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

int	wr_heredoc(t_command *cmd, t_lexer_token *red)
{
	char	*l;
	int		fd;

	(void)cmd;
	fd = open("tmp_XmXiXnXiXsXhXeXlXl", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		exit(mini_perr("minishell: ", red->str, 1, 0));
	while (1)
	{
		l = readline(">");
		if (ft_strncmp(l, red->str, ft_strlen(red->str) + 1) == 0)
			break ;
		ft_putendl_fd(l, fd);
		free(l);
	}
	free(l);
	close(fd);
	exit(0);
}

int	red_heredoc(t_command *cmd, t_lexer_token *red)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid == 0)
	{
		heredoc_sig_config();
		wr_heredoc(cmd, red);
	}
	else if (pid < 0)
		return (mini_perr("minishell: ", "fork", 1, -1));
	sig_ignore();
	waitpid(pid, &g_exit_status, 0);
	if (WEXITSTATUS(g_exit_status) != 0)
		return (-1);
	sig_config();
	fd = open("tmp_XmXiXnXiXsXhXeXlXl", O_RDONLY);
	if (fd == -1 || unlink("tmp_XmXiXnXiXsXhXeXlXl") == -1)
		mini_perr("minishell:", "tmp_XmXiXnXiXsXhXeXlXl", 1, 0);
	return (fd);
}
