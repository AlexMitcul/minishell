/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:42:46 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/21 16:15:15 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# define LEXER_H

# include <stdio.h>

# include <stdio.h>

# include "minishell.h"
# include "utils.h"

# define DELIMETERS " <>;$\"\'`\\"

t_dll_item	*lexer(char *input);

// Utils functions
bool		is_whitespace_line(char	*line);
void		print_lexer_token(void *token);
void		free_lexer_token(void *token);

#endif
