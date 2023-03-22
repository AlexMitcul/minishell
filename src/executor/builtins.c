/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:50:59 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/22 14:53:09 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

t_builtin	*is_our_builtin(char *command)
{
	static t_builtin_def	funcs[BUILTINS_COUNT] = {
	{"echo", ft_echo},
	{"cd", ft_cd},
	{"pwd", ft_pwd},
	{"export", ft_export},
	{"unset", ft_unset},
	{"env", ft_env},
	{"exit", ft_exit},
	};
	int						size;
	int						i;

	size = ft_strlen(command);
	i = 0;
	while (i < BUILTINS_COUNT)
	{
		if (ft_strncmp(command, funcs[i].name, size) == 0)
			return (funcs[i].func);
		i++;
	}
	return (NULL);
}

char	*find_builtin_path(t_app *self, char *command_name)
{
	char		*path;
	char		*command;
	char		**splitted;
	int			i;

	path = find_list_value_by_key(self->env_list, "PATH");
	if (!path)
		return (NULL);
	splitted = ft_split(path, ':');
	free(path);
	command = ft_strjoin("/", command_name);
	i = 0;
	while (splitted[i])
	{
		path = ft_strjoin(splitted[i], command);
		if (access(path, X_OK) == 0)
			return (free(command), free_array(splitted), path);
		free(path);
		i++;
	}
	return (free(command), free_array(splitted), NULL);
}
