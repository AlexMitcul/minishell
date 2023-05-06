/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:39:34 by amitcul           #+#    #+#             */
/*   Updated: 2023/05/06 14:41:32 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
} t_env_list;

typedef enum s_token_type
{
	PIPE = 1,
	GREAT,
	G_GREAT,
	LESS,
	L_LESS
}	t_token_type;

typedef struct s_lexer_token
{
	int						index;
	char					*str;
	t_token_type			token_type;
	struct s_lexer_token	*next;
	struct s_lexer_token	*prev;

}	t_lexer_token;

typedef struct s_app
{
	t_env_list			*env_list;
	char				**envp;
	char				*input;
	t_lexer_token		*lexer_tokens;
} t_app;

#endif
