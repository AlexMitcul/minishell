/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:58:21 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/19 17:02:38 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static	int	set_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (WTERMSIG(status));
}

int	run(t_app *self, t_command *command)
{
	int	stdout_fd;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		stdout_ft = dup(STDOUT_FILENO);
		run_setup_io(self, command);
		find_binary_path(self->envp, command);
		if (execve(*command->argv, command->argv, get_env_raw(self)) == -1)
		{
			dup2(stdout_fd, STDOUT_FILENO);
			run_exit_error(command->argv[0]);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	return (set_status(status));
}
