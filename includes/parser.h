/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:21:06 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/08 20:43:56 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>

# include "structs.h"
# include "libft.h"

typedef struct	s_parser
{
	t_lexer_token	*lexer_list;
	t_lexer_token	*redirs;
	int				redirs_count;
	struct s_app	*app;
}	t_parser;


/*
	echo $PATH hello $home hello world
	{"echo", "...", "hello", "..."}
*/

typedef struct s_command
{
	int					fd[2]; // N
	char				**str;
	int 				(*builtin)(t_app *, char **);
	size_t				redirs_count;
	t_lexer_token		*redirs;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

int	parser(t_app *app);

t_command *get_command(t_parser *parser);
void add_command_to_list(t_app *app, t_command *new);
char *delete_quotes(char *str, char c);
void delete_node_by_index(t_lexer_token **list, size_t index);
void collect_redirections(t_parser *parser);

#endif
