/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:49:35 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/02 13:44:13 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->data);
		free(tmp);
	}
}

t_lexer	*init_lexer(char *line)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->state = DEFAULT;
	lexer->line = line;
	lexer->line_size = ft_strlen(line);
	lexer->token = init_token(lexer->line_size);
	lexer->line_i = 0;
	lexer->token_i = 0;
	lexer->curr_char = 0;
	lexer->type = 0;
	return (lexer);
}

t_token	*init_token(int line_size)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->data = (char *)ft_calloc(line_size + 1, sizeof(char));
	token->type = NONE;
	token->next = NULL;
	return (token);
}

static char	*get_string_type(int type)
{
	if (type == DEFAULT)
		return ("DEFAULT");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == QUOTES)
		return ("QUOTES");
	else if (type == DQUOTES)
		return ("DOUBLE QUOTES");
	else if (type == WS)
		return ("WHITESPACE");
	else if (type == GREAT)
		return ("GREAT");
	else if (type == GGREAT)
		return ("GREAT GREAT");
	else if (type == LESS)
		return ("LESS");
	else if (type == LLESS)
		return ("LESS LESS");
	return ("NONE");
}

void	print_lexer_tokens(t_token *token)
{
	int		i;

	i = 0;
	printf("=== TOKEN LIST ===\n");
	while (token)
	{
		printf("%3d | %15s\n", i, get_string_type(token->type));
		printf("%s\n", token->data);
		token = token->next;
		i++;
	}
}
