/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:21:06 by amitcul           #+#    #+#             */
/*   Updated: 2023/05/21 12:13:27 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <stdlib.h>

# include "structs.h"
# include "libft.h"

typedef enum s_parser_error
{
    SYNTAX_ERROR = 42,
    COMMAND_NOT_FOUND,
    PERMISSION_DENIED,
    NO_SUCH_FILE_OR_DIR,
    VAR_NOT_FOUND,
    REDIRECT,
    MEMORY_ERROR,
    PLACEHOLDER
}	t_parser_error;

typedef struct	s_parser
{
    t_lexer_token	*lexer_list;
    t_lexer_token	*redirs;
    int				redirs_count;
    struct s_app	*app;
}	t_parser;



typedef struct s_command
{
    char				**str;
	int 				(*builtin)(t_app *, char **);
    char                *heredoc;
    size_t				redirs_count;
    t_lexer_token		*redirs;
    struct s_command	*next;
    struct s_command	*prev;
}	t_command;

t_command *get_command(t_parser *parser);
void add_command_to_list(t_app *app, t_command *new);

char *delete_quotes(char *str, char c);

void delete_node_by_index(t_lexer_token **list, size_t index);

void collect_redirections(t_parser *parser);

#endif
