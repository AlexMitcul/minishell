/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:45:45 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/02 21:37:44 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	lexer(t_app *app)
{
	char	*t;

	#ifdef DEBUG
	(void)t;
	#else
	ft_putstr_fd("hello", STDOUT_FILENO);
	app->input = readline(PROMPT);
	t = ft_strtrim(app->input, " ");
	free(app->input);
	app->input = t;
	#endif
	if (app->input[0] == '\0')
		return (L_RESET);
	add_history(app->input);
	if (!check_quotes(app->input))
		return (L_QUOTES_ERR);
	if (!get_tokens(app))
		return (L_TOKEN_ERR);
	return (EXIT_SUCCESS);
}
