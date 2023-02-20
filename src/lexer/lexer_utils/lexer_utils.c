/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:12:30 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/20 14:15:54 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"

void	print_lexer_token(void *token)
{
	printf("%s\n", (char *)token);
}

void	free_lexer_token(void *token)
{
	free((char *)token);
}

bool	is_whitespace_line(char	*line)
{
	if (line == NULL)
		return (true);
	while (*line)
	{
		if (*line != ' ')
			return (false);
		line++;
	}
	return (true);
}
