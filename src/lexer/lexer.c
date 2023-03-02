/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:19:13 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/18 17:00:34 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	get_type(char c)
{
	if (c == QUOTES
		|| c == DQUOTES
		|| c == PIPE
		|| c == GREAT
		|| c == LESS
		|| c == WS
		|| c == NONE)
		return (c);
	else
		return (DEFAULT);
}

void	lexer_state_quote(t_lexer *lexer)
{
	lexer->token->data[lexer->token_i] = lexer->curr_char;
	if (lexer->type == QUOTES)
		lexer->state = DEFAULT;
}

void	recognize_token(t_lexer *lexer, char *line)
{
	lexer->curr_char = line[lexer->line_i];
	lexer->type = get_type(lexer->curr_char);
	if (lexer->state == DEFAULT)
		default_state_handler(lexer);
	else if (lexer->state == QUOTES || lexer->state == DQUOTES)
		quotes_state_handler(lexer);
	lexer->line_i++;
}

// free lexer
t_token	*lexer(t_app *self, char *line)
{
	t_lexer	*lexer;
	t_token	*head;

	lexer = init_lexer(line);
	head = lexer->token;
	while (line[lexer->line_i])
		recognize_token(lexer, line);
	recognize_token(lexer, line);
	lexer->token = head;
	expand(self, lexer->token);
	free(lexer);
	return (head);
}
