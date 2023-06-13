/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshells.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:44:11 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/13 20:47:58 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

int	waiter(t_command *commands_list)
{
	t_command	*cmd;
	int			wstatus;

	cmd = commands_list;
	wstatus = 0;
	while (cmd)
	{
		if (waitpid(0, &wstatus, 0) == -1)
			return (mini_perr("minishell: ", "waitpid", 1, 0));
		cmd = cmd->next;
	}
	g_exit_status = WEXITSTATUS(wstatus);
	return (g_exit_status);
}

int	killer(t_command *commands_list)
{
	t_command	*cmd;

	cmd = commands_list;
	while (cmd)
	{
		if (cmd->pid != 0)
			kill(cmd->pid, SIGKILL);
		cmd = cmd->next;
	}
	return (0);
}
