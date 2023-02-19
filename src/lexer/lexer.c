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

#define DELIMETERS " <>;$\"\'`\\"

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
	if ((*line)[j] == '\0')
		return (NULL);
	if (i - j == 0)
		token = ft_substr(*line, i, 1);
	else
		token = ft_substr(*line, i, j - i);
	(*line) += ft_strlen(token);
	return (token);
}

int	lexer(t_dll_item *list, char *input)
{
	char		*token;
	char		*copy_input;

	copy_input = input;
	token = get_token(&copy_input);
	while (token != NULL)
	{
		if (is_whitespace(token) == false)
			dll_append(&list, (void *)token);
		free(token);
		token = get_token(&copy_input);
	}
	return (EXIT_SUCCESS);
}
