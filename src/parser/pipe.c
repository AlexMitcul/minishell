/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:04:28 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/01 17:06:26 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_tree	*try_parse_pipe(t_parser *parser)
{
	t_tree	*node;
	t_tree	*left;
	t_tree	*right;

	left = try_parse_redirect(parser);
	if (!left)
		return (NULL);
	if (!match(PIPE, NULL, parser))
		return (tree_destroy(left), NULL);
	right = try_parse(parser);
	if (!left)
		return (tree_destroy(left), NULL);
	node = init_node(PIPE);
	node->left = left;
	node->right = right;
	return (node);
}
