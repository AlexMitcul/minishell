/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:09:01 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/15 18:41:01 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern int	g_exit_status; // extern

int	ft_env(t_app *self, char **args)
{
	t_env_list	*tmp;

	if (args[1])
		return (mini_err("env: `", args[1], \
			"`: No such file or directory", 127));
	tmp = self->env_list;
	while (tmp)
	{
		ft_putstr_fd(tmp->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(tmp->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		tmp = tmp->next;
	}
	g_exit_status = 0;
	return (g_exit_status);
}
