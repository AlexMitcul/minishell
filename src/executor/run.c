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
	(void)self;
	(void)command;

	pid_t	pid;

	pid = fork();
	if (pid < 0)
		printf("error when forking\n");
	else if (pid == 0)
	{
		if (execve(command->argv[0], command->argv, self->envp) < 0)
		{
			printf("error when executing\n");
		}
	}
}
