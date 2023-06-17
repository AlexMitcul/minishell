/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:53:23 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/15 18:56:18 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(t_env_list *env_list, char *key)
{
	t_env_list	*tmp;

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

int	env_list_size(t_env_list *env_list)
{
	int			size;
	t_env_list	*tmp;

	size = 0;
	tmp = env_list;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

t_app	*env_list_dup(t_env_list *env_list)
{
	t_app		*new;
	t_env_list	*tmp;

	tmp = env_list;
	new = malloc(sizeof(t_app));
	ft_bzero(new, sizeof(t_app));
	while (tmp)
	{
		if (tmp->value == NULL)
			push_front(new, init(ft_strdup(tmp->key), NULL));
		else
			push_front(new, init(ft_strdup(tmp->key), ft_strdup(tmp->value)));
		tmp = tmp->next;
	}
	return (new);
}
