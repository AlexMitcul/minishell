/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:31:06 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/21 21:53:16 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

typedef struct s_command
{
	size_t	argc;
	char	**argv;
}	t_command;

static size_t	get_depth(t_tree *node)
{
	size_t	depth;

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

t_command	*build_command(t_app *self, t_tree *root)
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

void	executor(t_app *self, t_tree *root)
{
	t_command	*command;

	if (root->type == CMDPATH_NODE)
	{
		command = build_command(self, root);
		execute_command(command);
	}
}
