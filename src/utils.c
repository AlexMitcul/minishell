//
// Created by amitcul on 6/3/23.
//

#include "../includes/minishell.h"

void	remove_list_item_by_key(t_app *self, char *key)
{
	t_env_list	*tmp;
	t_env_list	*prev;

	tmp = self->env_list;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev == NULL)
				self->env_list = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}