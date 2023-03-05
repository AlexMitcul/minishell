/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:05:07 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/05 15:48:10 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	command_init(t_tree *root, t_exec *exec)
{
	t_tree	*node;
	int		args_count;

	if (!root || root->type == ARGUMENT_NODE)
		return ;
	args_count = 0;
	node = root;
	while (node && (node->type == ARGUMENT_NODE || node->type == CMDPATH_NODE))
	{
		node = node->right;
		args_count++;
	}
	exec->args = ft_calloc(args_count + 1, sizeof(char *));
	args_count = 0;
	node = root;
	while (node && (node->type == ARGUMENT_NODE || node->type == CMDPATH_NODE))
	{
		exec->args[args_count] = ft_strdup(node->data);
		node = node->right;
		args_count++;
	}
}

static bool	try_run_our_builtin(t_app *self, t_exec *exec)
{
	static char	*our_functions[BUILTINS_COUNT] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit"
	};
	static int (*ft_builtins[BUILTINS_COUNT])(t_app *, char **) = {
		ft_echo, ft_cd, ft_pwd, ft_export, ft_unset, ft_env, ft_exit
	};
	int	i;

	i = 0;
	while (i < BUILTINS_COUNT)
	{
		if (ft_strncmp(our_functions[i], exec->args[0],
			ft_strlen(parse) + 1) == 0)
		{
			ft_builtins[i](self, exec->args);
			return (true);
		}
		i++;
	}
	return (false);
}

void	command_execute(t_app *self, t_exec *exec)
{
	char	*builtin;

	if (exec->args == NULL)
		return ;
	if (try_run_our_builtin(self, exec))
		return ;
	run_builtin(self, exec);
}
