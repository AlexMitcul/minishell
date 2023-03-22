/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:52:11 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/22 14:52:19 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_list_value_by_key(t_env_list *list, char *key)
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
