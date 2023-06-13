/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:45:14 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/13 20:49:36 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

char	*pathsearch(char *cmd, char **paths)
{
	char *tmp[2];
	int i;

	i = -1;
	while (paths && paths[++i])
	{
		tmp[0] = ft_strjoin(paths[i], "/");
		if (tmp[0] == NULL)
			return (NULL);
		tmp[1] = ft_strjoin(tmp[0], cmd);
		if (tmp[1] == NULL)
			return (NULL);
		free(tmp[0]);
		if (access(tmp[1], F_OK) == 0)
			return (tmp[1]);
		free(tmp[1]);
	}
	mini_err(NULL, cmd, ": command not found", 127);
	return (NULL);
}

static char	*get_env_value(char *key, t_env_list *env_list)
{
	t_env_list *tmp;

	if (!env_list)
		return (NULL);
	tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*cmdpath(char *cmd, t_env_list *envl) // free cmd
{
	char **paths;
	char *env_path;
	char *cpath;

	env_path = get_env_value("PATH", envl);
	if ((ft_strchr(cmd, '/') || !env_path) && access(cmd, F_OK) == -1)
	{
		mini_err("minishell: ", cmd, ": No such file or directory", 127);
		return (NULL);
	}
	if (ft_strchr(cmd, '/') || isbuiltin(cmd)) // also check for PATH
		return (cmd);
	paths = ft_split(env_path, ':');
	cpath = pathsearch(cmd, paths);
	ft_splitfree(paths);
	return (cpath);
}