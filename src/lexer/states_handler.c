/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:55:07 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/25 16:56:44 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	quotes_state_handler(t_lexer *lexer)
{
	lexer->token->data[lexer->token_i] = lexer->curr_char;
	lexer->token_i++;
	if (lexer->type == QUOTES || lexer->type == DQUOTES)
		lexer->state = DEFAULT;
}

void	default_state_handler(t_lexer *lexer)
{
	if (lexer->type == QUOTES || lexer->type == DQUOTES)
		quotes_handler(lexer);
	else if (lexer->type == WS)
		whitespace_handler(lexer);
	else if (lexer->type == DEFAULT)
		default_handler(lexer);
	else if (lexer->type == GREAT || lexer->type == LESS || lexer->type == PIPE)
		redirect_handler(lexer);
}
