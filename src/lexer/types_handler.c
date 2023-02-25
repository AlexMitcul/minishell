/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:58:31 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/25 18:51:16 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	quotes_handler(t_lexer *lexer)
{
	if (lexer->type == QUOTES)
	{
		lexer->state = STATE_QUOTES;
		lexer->token->data[lexer->token_i] = QUOTES;
	}
	else if (lexer->type == DQUOTES)
	{
		lexer->state = STATE_DQUOTES;
		lexer->token->data[lexer->token_i] = DQUOTES;
	}
	lexer->token_i++;
	lexer->token->type = DEFAULT;
}

void	whitespace_handler(t_lexer *lexer)
{
	end_token(lexer);
}

void	default_handler(t_lexer *lexer)
{
	lexer->token->type = DEFAULT;
	lexer->token->data[lexer->token_i] = lexer->curr_char;
	lexer->token_i++;
}

void	redirect_handler(t_lexer *lexer)
{
	end_token(lexer);
	lexer->token->data[0] = lexer->curr_char;
	if (lexer->curr_char != PIPE && lexer->line[lexer->line_i + 1]
		&& lexer->line[lexer->line_i + 1] == lexer->curr_char)
	{
		if (lexer->curr_char == GREAT)
			lexer->type = GGREAT;
		else if (lexer->curr_char == LESS)
			lexer->type = LLESS;
		lexer->token->data[1] = lexer->curr_char;
		lexer->line_i++;
	}
	lexer->token_i++;
	lexer->token->type = lexer->type;
	end_token(lexer);
}

// If the statement is to not add an empty token, like whitespace
void	end_token(t_lexer *lexer)
{
	if (lexer->token_i <= 0)
		return ;
	lexer->token->next = init_token(lexer->line_size);
	lexer->token = lexer->token->next;
	lexer->token_i = 0;
}
