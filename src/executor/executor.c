/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:29:20 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/05 15:23:24 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

int	execute_pipe(t_app *self, t_tree *tree)
{
	(void)tree;
	(void)self;
	return (EXIT_SUCCESS);
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

void	execute_simple_command(t_app *self, t_tree *node, t_exec exec)
{
	int	i;

	command_init(node, &exec);
	command_execute(self, &exec);
	i = 0;
	while (exec.args && exec.args[i])
		free(exec.args[i++]);
	free(exec.args);
}

int	execute_command(t_app *self, t_tree *tree)
{
	if (is_redirect(tree->type))
	{
		// execute_redirect();
		execute_simple_command(self, tree,
			(t_exec){NULL, false, false, 0, 0});
	}
	else if (tree->type == CMDPATH_NODE)
	execute_simple_command(self, tree,
			(t_exec){NULL, false, false, 0, 0});
	return (EXIT_SUCCESS);
}

int	execute_tree(t_app *self, t_tree *tree)
{
	int	status;

	if (!self || !tree)
		return (EXIT_FAILURE);
	status = EXIT_SUCCESS;
	if (tree->type == PIPE_NODE)
		status = execute_pipe(self, tree);
	else
		status = execute_command(self, tree);
	return (status);
}
