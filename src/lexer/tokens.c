/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:54:30 by amitcul           #+#    #+#             */
/*   Updated: 2023/05/16 20:32:02 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

//! Need to move this function to libft
int	ft_iswhitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

t_token_type	is_token(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (GREAT);
	else if (c == '<')
		return LESS;
	return (0);
}

int	handle_token(char *str, int start, t_lexer_token **list)
{
	t_token_type	token_type;

	token_type = is_token(str[start]);
	if (!token_type)
		return (0);
	if (token_type == GREAT && is_token(str[start + 1]) == GREAT)
		token_type = G_GREAT;
	else if (token_type == LESS && is_token(str[start + 1]) == LESS)
		token_type = L_LESS;
	if (!add_node(NULL, token_type, list))
		return (-1);
    if (token_type == G_GREAT || token_type == L_LESS)
        return (2);
    return (1);
}

int	read_word(int start, char *str, t_lexer_token **list)
{
	int	i;

	i = 0;
	while (str[start + i] && !(is_token(str[start + i])))
	{
		i += handle_quotes(start + i, str, '"');
		i += handle_quotes(start + i, str, '\'');
		if (ft_iswhitespace(str[start + i]))
			break ;
		i++;
	}
	if (!add_node(ft_substr(str, start, i), 0, list))
		return (-1);
	return (i);
}

int	get_tokens(t_app *app)
{
	int	i;
	int	j;

	i = 0;
	while (app->input[i])
	{
		j = 0;
		while (ft_iswhitespace(app->input[i]))
			i++;
		if (is_token(app->input[i]))
			j = handle_token(app->input, i, &app->lexer_tokens);
		else
			j = read_word(i, app->input, &app->lexer_tokens);
		if (j < 0)
			return 0;
		i += j;
	}
	return (1);
}
