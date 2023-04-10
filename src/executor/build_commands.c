/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:02:06 by amitcul           #+#    #+#             */
/*   Updated: 2023/04/10 17:38:53 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"
void    print_command_list(t_command_list *list)
{
    t_command *curr;

    if (!list)
        printf("== List doen't exist ==\n");
    else
    {
        curr = list->command;
        if (!curr)
            printf("== List is empty ==\n");
        while (curr)
        {
            print_command(curr);
            curr = curr->next;
        }
    }
}

void    push_back(t_command_list *list, t_command *item)
{
    t_command   *curr;

    // printf("here2\n");
    if (!list || !item)
        return ;
    if (!list->command)
    {
        list->command = item;
    }
    else
    {
        curr = list->command;
        while (curr->next)
            curr = curr->next;
        curr->next = item;
    }
}

bool is_redirect_node(t_node type)
{
    return (type == REDIRECT_IN_NODE || type == REDIRECT_OUT_NODE 
            || type == HEREDOC_NODE || type == APPEND_NODE);
}

void	traverse_tree(t_tree *root, t_command_list *list)
{
	if (!root)
		return ;
	if (root->type == PIPE_NODE)
	{
		printf("%s\n", root->data);
	} else if (root->type == CMDPATH_NODE) {
		printf("Need to build command: %s\n", root->data);
        push_back(list, build_command(root));
	} else if (is_redirect_node(root->type)) {
        printf("Need to build rederict node: %s\n", root->data);
        push_back(list, build_command(root));
    }
    traverse_tree(root->left, list);
    traverse_tree(root->right, list);
}

void    distribute_fd(t_command_list *list)
{
    (void)list;
}

t_command_list  *build_command_list(t_app *self, t_tree *root)
{
    t_command_list  *list;
    (void)self;

    list = malloc(sizeof(t_command_list));
    list->command = NULL;
    // printf("here\n");
    traverse_tree(root, list);
    print_command_list(list);
    distribute_fd(list);

    return (NULL);
}