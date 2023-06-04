/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:59:35 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/23 15:01:04 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void	run_builtin(t_app *self, t_command *command)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		printf("error when forking\n");
	else if (pid == 0)
	{
		if (execve(command->argv[0], command->argv, self->envp) < 0)
		{
			printf("error when executing\n");
		}
	} else {
		/* parent sub programm */
		;
	}

	/*
	WIFEXITED(status)
		returns true if the child terminated normally, that is, by calling 
		exit(3) or _exit(2), or by returning from main().

   WEXITSTATUS(status)
		returns  the  exit status of the child.  This consists of the least 
		significant 8 bits of the status argument that the child specified in 
		a call to exit(3) or _exit(2) or as the argument for a
		return statement in main().  This macro should be employed only 
		if WIFEXITED returned true.
	*/

	// ! Need to handle this status code and replace with our global variable I guess
	// ! Like g_status = WEXITSTATUS(status);
	pid = waitpid(pid, &status, 0);
	if (pid < 0)
		printf("Error uccured\n");
	// Debug print
	if (WIFEXITED(status))
        printf("exit status = %d\n", WEXITSTATUS(status));
}
