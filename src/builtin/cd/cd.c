/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 01:46:06 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/17 16:46:22 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static int	set_pwd(t_env_list *env_list, char *oldpwd)
{
	char		*pwd;
	t_env_list	*tmp;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (mini_perr(PRE, "cd", 1, 0));
	tmp = env_list;
	while (env_list)
	{
		if (ft_strncmp(env_list->key, "OLDPWD", 7) == 0)
		{
			free(env_list->value);
			env_list->value = oldpwd;
		}
		if (ft_strncmp(env_list->key, "PWD", 4) == 0)
		{
			free(env_list->value);
			env_list->value = pwd;
		}
		env_list = env_list->next;
	}
	env_list = tmp;
	return (EXIT_SUCCESS);
}

// static int	chto_home(t_env_list *env_list, char *oldpwd)
static int	chto_home(t_env_list *env_list)
{
	char	*home;

	home = get_env_value(env_list, "HOME");
	if (home == NULL)
		return (mini_err(PRE, "cd: ", "HOME not set", 1));
	if (chdir(home) != EXIT_SUCCESS)
		return (mini_perr(PRE "cd: ", home, 1, 0));
	// set_pwd(env_list, oldpwd);
	g_exit_status = 0;
	return (g_exit_status);
}

int	ft_cd(t_app *self, char **args)
{
	char	*oldpwd;

	if (count_args(args) > 2)
		return (mini_err(PRE, "cd: ", "too many arguments", 1));
	// oldpwd = ft_strdup(get_env_value(self->env_list, "PWD"));
	oldpwd = getcwd(NULL, 0);
	if (args[1] == NULL)
	{
		if (chto_home(self->env_list) != EXIT_SUCCESS)
			return (g_exit_status);
	}
	else
	{
		if (chdir(args[1]) != EXIT_SUCCESS)
			return (mini_perr(PRE "cd: ", args[1], 1, 0));
		// set_pwd(self->env_list, oldpwd);
		g_exit_status = 0;
	}
	set_pwd(self->env_list, oldpwd);
	return (g_exit_status);
}
