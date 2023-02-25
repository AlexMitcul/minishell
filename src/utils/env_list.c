/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:08:03 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/25 19:35:39 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env_list	*init(char *key, char *value)
{
	t_env_list	*new;

	new = malloc(sizeof(t_env_list));
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

static void	push_front(t_app *self, t_env_list *new)
{
	if (new == NULL)
		return ;
	if (self->env_list == NULL)
	{
		self->env_list = new;
		return ;
	}
	new->next = self->env_list;
	self->env_list = new;
}

void	fill_env_list(t_app *self, char **envp)
{
	int		i;
	int		index;
	char	*start;

	i = 0;
	while (envp[i + 1])
		i++;
	while (envp[i])
	{
		start = ft_strchr(envp[i], '=');
		index = (int) (start - envp[i]);
		if (start == NULL)
			index = ft_strlen(envp[i]);
		push_front(self, init(ft_substr(envp[i], 0, index),
			ft_substr(envp[i], index + 1, ft_strlen(envp[i]))));
		i--;
	}
	self->envp = envp;
}
