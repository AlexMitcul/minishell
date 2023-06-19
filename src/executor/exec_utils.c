/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:51:21 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/15 18:45:05 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

extern int	g_exit_status;

int	mini_err(char *pre, char *name, char *msg, int exit_status)
{
	ft_putstr_fd(pre, STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	g_exit_status = exit_status;
	return (g_exit_status);
}

int	mini_perr(char *pre, char *name, int exit_status, int fail)
{
	ft_putstr_fd(pre, STDERR_FILENO);
	perror(name);
	g_exit_status = exit_status;
	if (fail == -1)
		return (-1);
	return (g_exit_status);
}

void	ft_splitfree(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

char	**getenvp(t_env_list *env_list)
{
	char		**envp;
	char		*tmp;
	int			i;
	t_env_list	*tmp_lst;

	envp = malloc(sizeof(char *) * (env_list_size(env_list) + 1));
	if (!envp)
		return (NULL);
	envp[env_list_size(env_list)] = NULL;
	tmp = NULL;
	tmp_lst = env_list;
	i = 0;
	while (tmp_lst)
	{
		tmp = ft_strjoin(tmp_lst->key, "=");
		envp[i] = ft_strjoin(tmp, tmp_lst->value);
		free(tmp);
		tmp_lst = tmp_lst->next;
		i++;
	}
	return (envp);
}
