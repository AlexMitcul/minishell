/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:21:06 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/01 16:05:18 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "../libft/includes/libft.h"

# include <stdlib.h>

typedef struct s_app		t_app;
typedef struct s_tree		t_tree;
typedef struct s_parser		t_parser;
typedef struct s_token		t_token;
typedef struct s_lexer		t_lexer;
typedef struct s_env_list	t_env_list;

typedef enum e_node
{
	PIPE_NODE = 1,
	REDIRECT_IN_NODE,
	REDIRECT_OUT_NODE,
	HEREDOC_NODE,
	APPEND_NODE,
	CMDPATH_NODE,
	ARGUMENT_NODE,
	NODE_DATA,
}	t_node;

struct s_parser
{
	t_token	*curr_token;
};

struct s_tree
{
	int				type;
	char			*data;
	struct s_tree	*left;
	struct s_tree	*right;
};

/* parser.c */
int		parse(t_token *tokens, t_tree **astree);
t_tree	*redirect(t_parser *parser);
t_tree	*try_parse(t_parser *parser);

/* tree.c */
t_tree	*init_node(int type);
void	tree_destroy(t_tree *node);
void	print_tree(t_tree *root, int level);

/* compare.c */
bool	match(int token_type, char **buffer, t_parser *parser);

/* pipe.c */
t_tree	*try_parse_pipe(t_parser *parser);

/* redirect.c */
t_tree	*try(t_parser *parser, int type);
t_tree	*try_parse_redirect(t_parser *parser);
t_tree	*identify_redirect_command_node(t_parser *parser);
t_tree	*redirect(t_parser *parser);
t_tree	*get_redirect_command_node(t_parser *parser, int type);

/* command.c */
t_tree	*command(t_parser *parser);
t_tree	*try_get_token_list(t_parser *parser);

#endif
