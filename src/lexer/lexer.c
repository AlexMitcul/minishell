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

char	*get_token(char **line)
{
	int		i;
	int		j;
	char	*token;

	if (*line == NULL)
		return (NULL);
	i = 0;
	j = i;
	while ((*line)[j] && ft_strchr(DELIMETERS, (*line)[j]) == NULL)
		j++;
	if ((*line)[j] == '\0' && j == 0)
		return (NULL);
	if (i - j == 0)
		token = ft_substr(*line, i, 1);
	else
		token = ft_substr(*line, i, j - i);
	(*line) += ft_strlen(token);
	return (token);
}

t_dll_item	*lexer(char *input)
{
	t_dll_item	*list;
	char		*token;

	list = NULL;
	token = get_token(&input);
	while (token != NULL)
	{
		dll_append(&list, token);
		token = get_token(&input);
	}
	return (list);
}
