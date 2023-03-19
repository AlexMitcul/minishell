/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:29:20 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/19 17:27:17 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void	execute_simple_command(t_app *self, t_tree *tree, t_exec exec)
{
	t_command	command;

	command = (t_command){0, NULL, false, false, 0, 0, 0, 0};
	command_init(tree, &command, exec);
	command_execute(self, &command);
	command_destroy(&command);
}

bool	is_redirect(int type)
{
	if (type == REDIRECT_IN_NODE
		|| type == REDIRECT_OUT_NODE
		|| type == HEREDOC_NODE
		|| type == APPEND_NODE)
		return (true);
	return (false);
}

int	execute_command(t_app *self, t_tree *tree, t_exec exec)
{
	if (is_redirect(tree->type))
	{
		;
	}
	else if (tree->type == CMDPATH_NODE)
		execute_simple_command(self, tree, exec);
	return (EXIT_SUCCESS);
}

int	execute_tree(t_app *self, t_tree *tree)
{
	int	status;

	if (!self || !tree)
		return (EXIT_FAILURE);
	status = EXIT_SUCCESS;
	if (tree->type == PIPE_NODE)
		; // status = execute_pipe(self, tree);
	else
		status = execute_command(self, tree,
			(t_exec){false, false, 0, 0, 0, 0});
	return (status);
}
