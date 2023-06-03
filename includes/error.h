//
// Created by amitcul on 6/3/23.
//

#ifndef ERROR_H
# define ERROR_H
# include "minishell.h"

void	parser_error(int error, t_app *app, t_lexer_token *lexer_list);
int		parser_double_token_error(t_app *app, t_lexer_token *lexer_list,
									 t_token_type token);
void	lexer_error(int error, t_app *app);
int		cmd_not_found(char *str);
int		export_error(char *c);

//ft_error
int		ft_error(int error, t_app *app);

#endif