/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:48:16 by amitcul           #+#    #+#             */
/*   Updated: 2023/05/06 16:04:08 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "structs.h"

# define L_RESET 1
# define L_QUOTES_ERR 2
# define L_TOKEN_ERR 3

int	lexer(t_app *app);

// quotes
int	check_quotes(char *line);
int	handle_quotes(int start, char *str, char quote);

// utils
int	add_node(char *str, t_token_type token_type, t_lexer_token **list);
t_lexer_token	*get_lexer_new_node(char *str, int token_type);

// tokens
int	get_tokens(t_app *app);

#endif
