/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:22:33 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/26 17:31:09 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_tree	*try_get_token(t_parser *parser)
{
	t_tree	*node;
	t_tree	*right;
	char	*data;

	if (!match(DEFAULT, &data, parser))
		return (NULL);
	right = try_get_token_list(parser);
	node = init_node(ARGUMENT_NODE);
	node->data = data;
	node->right = right;
	return (node);
}

t_tree	*try_get_token_list(t_parser *parser)
{
	t_token	*begin;
	t_tree	*node;

	begin = parser->curr_token;
	node = try_get_token(parser);
	if (node)
		return (node);
	parser->curr_token = begin;
	return (NULL);
}

t_tree	*command(t_parser *parser)
{
	t_tree	*node;
	t_tree	*right;
	char	*path;

	if (!match(DEFAULT, &path, parser))
		return (NULL);
	right = try_get_token_list(parser);
	node = init_node(CMDPATH_NODE);
	node->data = path;
	node->right = right;
	return (node);
}
