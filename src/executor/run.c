/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:58:21 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/19 17:41:59 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static	int	set_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (WTERMSIG(status));
}

void	print_errno(char *cmd, char *input)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (input)
	{
		ft_putstr_fd(input, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	perror("");
}

void	print_error(char *cmd, char *input, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (input)
	{
		ft_putstr_fd(input, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
}

static void	run_exit_error(char *name)
{
	if (errno == ENOENT)
	{
		if ((*name == '.' && *(name + 1) == '/') || *name == '/')
			print_errno(name, NULL);
		else
			print_error(name, NULL, "command not found");
		exit(127);
	}
	if (errno == EACCES)
	{
		print_errno(name, NULL);
		exit(126);
	}
}

int	run(t_app *self, t_command *command)
{
	(void)self;
	(void)command;
	int	stdout_fd;
	int	status;
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		stdout_fd = dup(STDOUT_FILENO);
		// run_setup_io(self, command);
		// find_binary_path(self->envp, command);
		// if (execve(*command->argv, command->argv, get_env_raw(self)) == -1)
		// {
		// 	dup2(stdout_fd, STDOUT_FILENO);
			run_exit_error(command->argv[0]);
		// }
	}
	else if (pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	return (set_status(status));
}
