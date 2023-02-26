/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:00:28 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/26 17:32:22 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

bool	match(int token_type, char **buffer, t_parser *parser)
{
	t_token	*token;

	token = parser->curr_token;
	if (!token)
		return (false);
	if (token->type == token_type)
	{
		if (buffer)
			*buffer = ft_strdup(token->data);
		parser->curr_token = token->next;
		return (true);
	}
	parser->curr_token = token->next;
	return (false);
}
