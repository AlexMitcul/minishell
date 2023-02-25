/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:01:22 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/25 20:42:48 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_value(t_env_list *lst, char *key)
{
	while (lst)
	{
		if (ft_strncmp(lst->key, key, ft_strlen(key)) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

static void	join_and_set_splitted_array(t_token *token, char **splitted)
{
	char	*res;
	int		i;

	res = ft_strdup(splitted[0]);
	i = 1;
	while (splitted[i])
	{
		res = ft_strjoin(res, splitted[i]);
		i++;
	}
	i = 0;
	while (splitted[i])
		free(splitted[i++]);
	free(splitted);
	free(token->data);
	token->data = res;
}

static void	try_to_expand(t_app *self, t_token *token)
{
	int		i;
	int		dollars_count;
	int		splitted_count;
	char	**splitted;
	char	*tmp;

	dollars_count = count_symbol_in_string(token->data, '$');
	if (dollars_count == 0)
		return ;
	splitted = ft_split(token->data, '$');
	splitted_count = 0;
	while (splitted[splitted_count])
		splitted_count++;
	i = 0;
	if (splitted_count > dollars_count)
		i = 1;
	while (splitted[i])
	{
		tmp = get_value(self->env_list, splitted[i]);
		free(splitted[i]);
		splitted[i] = tmp;
		i++;
	}
	join_and_set_splitted_array(token, splitted);
}

void	expand(t_app *self, t_token *token_list)
{
	t_token	*curr;

	curr = token_list;
	while (curr)
	{
		if (curr->type == DEFAULT)
			try_to_expand(self, curr);
		curr = curr->next;
	}
}
