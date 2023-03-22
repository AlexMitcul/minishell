/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:31:06 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/22 14:26:37 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

/*
 echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no
*/

// typedef struct s_builtin_def	t_builtin_def;
// typedef int (t_builtin_def)(t_app *, char **);

# define BUILTINS_COUNT 7

typedef int (t_builtin)(t_app *, char **);

typedef struct s_builtin_def
{
	char		*name;
	t_builtin	*func;
}	t_builtin_def;

static t_builtin	*is_our_builtin(char *command)
{
	static t_builtin_def funcs[BUILTINS_COUNT] = {
		{"echo", ft_echo},
		{"cd", ft_cd},
		{"pwd", ft_pwd},
		{"export", ft_export},
		{"unset", ft_unset},
		{"env", ft_env},
		{"exit", ft_exit},
	};
	int	size;
	int	i;

	size = ft_strlen(command);
	i = 0;
	while (i < BUILTINS_COUNT)
	{
		if (ft_strncmp(command, funcs[i].name, size) == 0) {
			return (funcs[i].func);
		}
		i++;
	}
	return (NULL);
}

static char	*find_list_value_by_key(t_env_list *list, char *key)
{
	int	size;

	if (!key || !list)
		return (NULL);
	size = ft_strlen(key);
	while (list)
	{
		if (ft_strncmp(key, list->key, size) == 0)
			return (ft_strdup(list->value));
		list = list->next;
	}
	return (NULL);
}

//! REPLACE WITH GENERAL FUNCTION
static void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i]);
	free(arr);
}

static char	*find_builtin_path(t_app *self, char *command)
{
	char		*path;
	char		**splitted;
	int			i;

	path = find_list_value_by_key(self->env_list, "PATH");
	if (!path)
		return (NULL);
	splitted = ft_split(path, ':');
	free(path);
	//! command = ft_strjoin(command, "/");
	i = 0;
	while (splitted[i])
	{
		path = ft_strjoin(splitted[i], command);
		if (access(path, X_OK) == 0)
			return (free_array(splitted), path);
		i++;
	}
	return (free_array(splitted), NULL);
}

void	execute_command(t_app *self, t_command *command)
{
	char		*path;
	t_builtin	*builtin;

	path = NULL;
	builtin = is_our_builtin(command->argv[0]);
	if (!builtin)
		; // execute our command
	else
		path = find_builtin_path(self, command->argv[0]);
	printf("path: %s\n", path);
}

void	executor(t_app *self, t_tree *root)
{
	t_command	*command;

	(void)self;
	if (root->type == CMDPATH_NODE)
	{
		command = build_command(root);
		print_command(command);
		execute_command(self, command);
	}
}
