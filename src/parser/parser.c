/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:38:56 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/26 17:36:20 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_tree	*try_parse(t_parser *parser)
{
	t_token	*begin;
	t_tree	*node;

	begin = parser->curr_token;
	node = try_parse_pipe(parser);
	if (node)
		return (node);
	parser->curr_token = begin;
	// node = try_parse_redirect(parser);
	// if (node)
	// 	return (node);
	// parser->curr_token = begin;
	return (NULL);
}

//TODO: Confirm that exit status is correct
int	parse(t_token *tokens, t_tree **astree)
{
	t_parser	parser;

	if (!tokens)
		return (-1);
	parser.curr_token = tokens;
	*astree = try_parse(&parser);
	if (parser.curr_token && parser.curr_token->type)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(parser.curr_token->data, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
