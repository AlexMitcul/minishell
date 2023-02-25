/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:42:46 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/25 19:04:21 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>

# include "minishell.h"
# include "utils.h"

# define DELIMETERS " <>;$\"\'`\\"

enum e_state {
	STATE_DEFAULT,
	STATE_QUOTES,
	STATE_DQUOTES,
};

/*
 * TEXT -> Plain text, line "echo" command
 * PIPE -> [|]
 * QUOTE -> Single quote [']
 * DQUOTE -> Double quote ["]
 * WS -> Whitespace [ ]
 * GREAT -> [>]
 * GGREAT -> [>>]
 * LESS -> [<]
 * LLESS -> [<<]
 * NONE -> End of line EOL
*/
enum e_token_type {
	DEFAULT = -1,
	PIPE = '|',
	QUOTES = '\'',
	DQUOTES = '\"',
	WS = ' ',
	GREAT = '>',
	GGREAT = -2,
	LESS = '<',
	LLESS = -3,
	NONE = 0,
};

/*
 * env vars
*/

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_app
{
	t_env_list	*env_list;
	char		**envp;
}	t_app;

typedef struct s_token
{
	int				type;
	char			*data;
	struct s_token	*next;
}	t_token;

/*
 * token -> sequence of parsed tokens
 * state -> current state of parsed subline
 * line -> copy of input line
 * line_size -> length of input line
 * line_i -> current index in input line
 * token_i -> current index when completing token data
 * curr_char ->
 * type -> type of token e_token_type
*/
typedef struct s_lexer
{
	t_token	*token;
	int		state;
	char	*line;
	int		line_size;
	int		line_i;
	int		token_i;
	char	curr_char;
	int		type;
}	t_lexer;

//* Token handlers

void	quotes_handler(t_lexer *lexer);
void	whitespace_handler(t_lexer *lexer);
void	redirect_handler(t_lexer *lexer);
void	default_handler(t_lexer *lexer);
void	end_token(t_lexer *lexer);

//* State handlers

void	default_state_handler(t_lexer *lexer);
void	quotes_state_handler(t_lexer *lexer);

//* Utils functions

void	init_lexer(t_lexer *lexer, char *line);
t_token	*init_token(int line_size);
void	print_lexer_tokens(t_lexer *lexer);

//* Expander
void	expand(t_app *self, t_token *token_list);

#endif
