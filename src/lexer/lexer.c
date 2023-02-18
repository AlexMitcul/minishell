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

#define S_SYMBOLS " <>;|'\""

typedef enum e_token_type
{
	TEXT,
	COMMAND,
	SPECIAL_SYMBOL,
	NO_TYPE
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = NO_TYPE;
	token->value = NULL;
	return (token);
}

void	free_dll(t_dll_item *list)
{
	t_dll_item	*curr;

	if (!list)
		return ;
	curr = list->next;
	while (curr)
	{
		free(curr->prev);
		curr = curr->next;
	}
	free(curr->prev);
}

void	free_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->value != NULL)
		free(token->value);
	free(token);
}

void	string_join(char **str, char *to_add)
{
	char	*new_str;

	if (to_add == NULL)
		return ;
	if (*str == NULL)
	{
		*str = to_add;
		return ;
	}
	new_str = ft_strjoin(*str, to_add);
	free(*str);
	free(to_add);
	*str = new_str;
}

t_token	*parse_quotes(char *input, int *i, int *j)
{
	(void)input;
	(void)i;
	(void)j;
	return (NULL);
}

t_token	*parse_redirects(char *input, int *i, int *j)
{
	(void)input;
	(void)i;
	(void)j;
	return (NULL);
}

int	parse_started_from_spec_symbol(char *input, t_token *token, int *i, int *j)
{
	if (input[*j] == '\'' || input[*j] == '\"')
		token = parse_quotes(input, i, j);
	else if (input[*j] == '<' || input[*j] == '>')
		token = parse_redirects(input, i, j);
	if (token == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_plain_text(t_token *token, char *input, int i, int *j)
{
	return (EXIT_SUCCESS);
}

t_token	*get_next_token(char **input)
{
	t_token	*token;
	int		i;
	int		j;
	int		status;

	token = init_token();
	if (!token)
		return (NULL);
	i = 0;
	while ((*input)[i] != '\0')
	{
		j = i + 1;
		if (ft_strchr(S_SYMBOLS, (*input)[j]) == NULL)
			status = parse_plain_text(token, *input, i, &j);
		else
			status = parse_started_from_spec_symbol(*input, token, &i, &j);
		if (status == EXIT_FAILURE)
			return (free_token(token), NULL);
		i = j;
	}
	return (token);
}

int	lexer(t_dll_item *token_list, char *input)
{
	t_dll_item	*list;
	t_token		*token;
	char		*tmp_input;

	list = NULL;
	token = get_next_token(&tmp_input);
	while (token != NULL)
	{
		dll_append(&list, (void *)token);
		get_next_token(&input);
	}
	token_list = list;
	return (EXIT_SUCCESS);
}
