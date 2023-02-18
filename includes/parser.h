/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:21:06 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/18 17:02:01 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSER_H
# define PARSER_H

# include "../libft/includes/libft.h"

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
