/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:31:06 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/23 14:46:42 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void	execute_command(t_app *self, t_command *command)
{
	char		*path;
	t_builtin	*builtin;

	path = NULL;
	builtin = is_our_builtin(command->argv[0]);
	if (builtin != NULL)
		;
	else
	{
		path = find_builtin_path(self, command->argv[0]);
		if (path)
		{
			free(command->argv[0]);
			command->argv[0] = path;
		}
		else
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(command->argv[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
		}
	}
}

void	executor(t_app *self, t_tree *root)
{
	t_command	*command;

	if (root->type == CMDPATH_NODE)
	{
		command = build_command(root);
		execute_command(self, command);
		print_command(command);
		free_command(command);
	}
}
