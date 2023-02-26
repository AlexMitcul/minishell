/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:13:21 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/26 17:47:57 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_tree	*init_node(int type)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	node->type = type;
	node->data = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	tree_destroy(t_tree *node)
{
	if (!node)
		return ;
	if (node->data)
		free(node->data);
	tree_destroy(node->left);
	tree_destroy(node->right);
	free(node);
}

static int	tree_depth(t_tree *node)
{
	int	left;
	int	right;

	if (!node)
		return (0);
	left = tree_depth(node->left);
	right = tree_depth(node->right);
	if (left > right)
		return (1 + left);
	return (1 + right);
}

static void	pprint_tree(t_tree *node, int depth)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
	printf("%s\n", node->data);
	pprint_tree(node->left, depth + 1);
	pprint_tree(node->right, depth + 1);
}

void	print_tree(t_tree *node)
{
	pprint_tree(node, tree_depth(node));
}
