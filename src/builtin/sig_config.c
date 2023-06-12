/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:07:47 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/12 20:57:38 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

static void	ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		// kill(0, SIGINT); // kill all child processes
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 128 + SIGINT;
		// printf("ctrl_c");
		// kill(0, SIGKILL); // kill all processes in the process group of the calling process
	}
}

// int	child_sig_config(void)
// {
// 	struct sigaction	sa_dfl_int;

// 	sa_dfl_int.sa_handler = SIG_DFL;
// 	sigemptyset(&sa_dfl_int.sa_mask);
// 	if (sigaction(SIGINT, &sa_dfl_int, NULL) == -1)
// 		return (mini_perr("minishell: ", "sigaction", 1, 0));
// 	return (0);
// }

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
