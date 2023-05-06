/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:13:21 by amitcul           #+#    #+#             */
/*   Updated: 2023/05/06 16:11:02 by amitcul          ###   ########.fr       */
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

static char	*get_type(t_tree *node)
{
	if (node->type == PIPE_NODE)
		return ("PIPE");
	if (node->type == REDIRECT_IN_NODE)
		return ("REDIRECT_IN_NODE");
	if (node->type == REDIRECT_OUT_NODE)
		return ("REDIRECT_OUT_NODE");
	if (node->type == HEREDOC_NODE)
		return ("HEREDOC_NODE");
	if (node->type == APPEND_NODE)
		return ("APPEND_NODE");
	if (node->type == CMDPATH_NODE)
		return ("CMDPATH_NODE");
	if (node->type == ARGUMENT_NODE)
		return ("ARGUMENT_NODE");
	return ("NODE_DATA");
}

void	print_tree(t_tree *root, int level, char ch)
{
	int	i;

	if (root == NULL)
		return ;
	i = 0;
	while (i < level)
	{
		if (i == level - 1)
			printf("%c ", ch);
		else
			printf("  ");
		i++;
	}
	printf("%s = %s\n", get_type(root), root->data);
	print_tree(root->left, level + 1, 'L');
	print_tree(root->right, level + 1, 'R');
	print_tree(root->left, level + 1, 'L');
	print_tree(root->right, level + 1, 'R');
}
