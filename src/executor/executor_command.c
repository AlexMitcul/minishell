/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:51:23 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/22 12:59:02 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static int	get_depth(t_tree *node)
{
	int	depth;

	if (node == NULL)
		return 0;
	depth = 1;
	while (node->right)
	{
		node = node->right;
		depth++;
	}
	return (depth);
}

void	free_command(t_command *command)
{
	int	i;

	if (!command)
		return ;
	i = 0;
	while (command->argv && command->argv[i])
		free(command->argv[i++]);
	free(command->argv);
	free(command);
}

t_command	*build_command(t_tree *root)
{
	int			i;
	t_tree		*node;
	t_command	*command;

	command = malloc(sizeof(t_command));
	command->argc = get_depth(root);
	command->argv = ft_calloc(command->argc, sizeof(char *) * (command->argc + 1));
	node = root;
	i = 0;
	while (node)
	{
		command->argv[i] = ft_strdup(node->data);
		i++;
		node = node->right;
	}
	command->argv[i] = NULL;
	return (command);
}
