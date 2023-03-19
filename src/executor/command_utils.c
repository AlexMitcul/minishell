/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:43:50 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/19 17:38:22 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

static	bool	is_node_argument(t_tree *node)
{
	if (!node)
		return (false);
	return (node->type == ARGUMENT_NODE || node->type == CMDPATH_NODE);
}

static	void	command_fill(t_command *command, t_exec executor)
{
	command->stdin_pipe = executor.stdin_pipe;
	command->stdout_pipe = executor.stdout_pipe;
	command->pipe_read = executor.pipe_read;
	command->pipe_write = executor.pipe_write;
	command->redirect_in = executor.redirect_in;
	command->redirect_out = executor.redirect_out;
}

void	command_init(t_tree *root, t_command *command, t_exec exec)
{
	int		i;
	t_tree	*node;

	if (!root || root->type != CMDPATH_NODE)
		return ;
	i = 0;
	node = root;
	while (is_node_argument(node))
	{
		node = node->right;
		i++;
	}
	command->argv = malloc(sizeof(char *) * (i + 1)); //! replace with calloc
	i = 0;
	node = root;
	while (is_node_argument(node))
	{
		command->argv[i] = ft_strdup(node->data);
		node = node->right;
		i++;
	}
	command->argv[i] = NULL;
	command->argc = i;
	command_fill(command, exec);
}

void	command_execute(t_app *self, t_command *command)
{
	t_bin	*prog;
	// int		status;
	(void)self;

	if (command->argc < 0)
		return ;
	prog = get_builtin(*command->argv);
	// if (!prog)
	// 	prog = run;
	// status = prog(comma)
	// handle status
}

void	redirect_free(t_io **io)
{
	t_io	*tmp;

	if (!io)
		return ;
	while (*io)
	{
		tmp = *io;
		*io = (*io)->next;
		free(tmp->data);
		free(tmp);
	}
}

void	command_destroy(t_command *command)
{
	int	i;

	i = 0;
	while (i < command->argc)
		free(command->argv[i++]);
	free(command->argv);
	if (command->redirect_in)
		redirect_free(&command->redirect_in);
	if (command->redirect_out)
		redirect_free(&command->redirect_out);
	command->argc = 0;
}
