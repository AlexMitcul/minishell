/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:38:49 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/26 17:29:00 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_tree	*try_parse_redirect(t_parser *parser)
{
	t_token	*begin;
	t_tree	*node;

	begin = parser->curr_token;
	node = redirect(parser);
	if (node)
		return (node);
	// parser->curr_token = begin;
	// node = command(parser);
	// if (node)
	// 	return (node);
	// parser->curr_token = begin;
	return (NULL);
}

static int	get_node_type(int type)
{
	if (type == LESS)
		return (REDIRECT_IN_NODE);
	if (type == GREAT)
		return (REDIRECT_OUT_NODE);
	if (type == LLESS)
		return (HEREDOC_NODE);
	if (type == GGREAT)
		return (APPEND_NODE);
	return (0);
}

t_tree	*get_redirect_command_node(t_parser *parser, int type)
{
	t_tree	*node;
	t_tree	*left;
	char	*filename;

	if (!match(type, NULL, parser))
		return (NULL);
	if (!match(DEFAULT, &filename, parser))
		return (free(filename), NULL);
	left = identify_redirect_command_node(parser);
	node = init_node(get_node_type(type));
	node->data = filename;
	node->left = left;
	return (node);
}

t_tree	*identify_redirect_command_node(t_parser *parser)
{
	t_tree	*node;
	int		i;
	int		redirect_set[4];

	redirect_set[0] = LESS;
	redirect_set[1] = GREAT;
	redirect_set[3] = LLESS;
	redirect_set[2] = GGREAT;
	i = 0;
	while (i < 4)
	{
		node = get_redirect_command_node(parser, redirect_set[i]);
		if (node)
			return (node);
		i++;
	}
	return (NULL);
}

static t_tree	*try(t_parser *parser, int type)
{
	t_tree	*node;
	t_tree	*left;
	t_tree	*right;
	char	*filename;

	right = command(parser);
	if (!right)
		return (NULL);
	if (!match(type, NULL, parser))
		return (tree_destroy(right), NULL);
	if (!match(DEFAULT, &filename, parser))
		return (free(filename), tree_destroy(right), NULL);
	left = identify_redirect_command_node(parser);
	node = init_node(get_node_type(type));
	node->data = filename;
	node->left = left;
	node->right = right;
	return (node);
}

t_tree	*redirect(t_parser *parser)
{
	t_tree	*node;
	int		i;
	int		redirect_set[4];

	redirect_set[0] = LESS;
	redirect_set[1] = GREAT;
	redirect_set[3] = LLESS;
	redirect_set[2] = GGREAT;
	i = 0;
	while (i < 4)
	{
		node = try(parser, redirect_set[i]);
		if (node)
			return (node);
		i++;
	}
	return (NULL);
}
