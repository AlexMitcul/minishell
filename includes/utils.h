/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:37:55 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/15 18:53:52 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include "minishell.h"

typedef struct s_dll_item
{
	void				*data;
	struct s_dll_item	*next;
	struct s_dll_item	*prev;
}	t_dll_item;

void		print_dll_list(t_dll_item *head_ref, void (*f)(void *));
void		dll_append(t_dll_item **head_ref, void *new_data);
void		dll_push(t_dll_item **head_ref, void *new_data);
void		free_dll_list(t_dll_item *head_ref, void (*f)(void *));

int			count_symbol_in_string(char *str, int ch);

t_env_list	*init(char *key, char *value);
void		push_front(t_app *self, t_env_list *new);


#endif
