/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:37:55 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/18 20:38:48 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

typedef struct s_dll_item
{
	void				*data;
	struct s_dll_item	*next;
	struct s_dll_item	*prev;
}	t_dll_item;

void	dll_append(t_dll_item **head_ref, void *new_data);
void	dll_push(t_dll_item **head_ref, void *new_data);

#endif
