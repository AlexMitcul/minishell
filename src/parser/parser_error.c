/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:03:45 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/03 21:55:35 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_redirect_str(t_lexer_token *token)
{
	t_token_type	type;

	type = token->token_type;
	if (type == PIPE)
		return ("|");
	else if (type == GREAT)
		return (">");
	else if (type == G_GREAT)
		return (">>");
	else if (type == LESS)
		return ("<");
	else if (type == L_LESS)
		return ("<<");
	else
		return ("");
}
