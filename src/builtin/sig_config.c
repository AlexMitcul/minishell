/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:07:47 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/14 16:12:28 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

static void	ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 128 + SIGINT;
	}
}

static void	chld_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_exit_status = 128 + SIGINT;
	}
}

static void	heredoc_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_exit_status = 128 + SIGINT;
		unlink("tmp_XmXiXnXiXsXhXeXlXl");
		exit(g_exit_status);
	}
}

int	heredoc_sig_config(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = &heredoc_ctrl_c;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		return (mini_perr("minishell: ", "sigaction", 1, 0));
	return (0);
}

int	chld_sig_config(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = &chld_ctrl_c;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		return (mini_perr("minishell: ", "sigaction", 1, 0));
	return (0);
}

int	sig_ignore(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		return (mini_perr("minishell: ", "sigaction", 1, 0));
	return (0);
}

int	sig_config(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	
	sa_quit.sa_handler = SIG_IGN;
	sa_int.sa_handler = &ctrl_c;
	sigemptyset(&sa_int.sa_mask);
	sigaddset(&sa_int.sa_mask, SIGINT);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		return (mini_perr("minishell: ", "sigaction", 1, 0));
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		return (mini_perr("minishell: ", "sigaction", 1, 0));
	return (EXIT_SUCCESS);
}
