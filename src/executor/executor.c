/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:29:20 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/03 13:46:33 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

int	execute_pipe(t_app *self, t_tree *tree)
{
	(void)tree;
	(void)self;
	return (EXIT_SUCCESS);
}

int	execute_command(t_app *self, t_tree *tree)
{
	(void)tree;
	(void)self;
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
