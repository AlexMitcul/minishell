/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:29:37 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/05 15:19:46 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

typedef struct s_app		t_app;
typedef struct s_tree		t_tree;
typedef struct s_parser		t_parser;
typedef struct s_token		t_token;
typedef struct s_lexer		t_lexer;
typedef struct s_env_list	t_env_list;
// typedef struct s_command	t_command;
typedef struct s_exec		t_exec;

struct s_exec
{
	char	**args;
	bool	in_pipe;
	bool	out_pipe;
	int		read_fd;
	int		write_fd;
};

int	execute_tree(t_app *self, t_tree *tree);

/* command_funcs.c */
void	command_init(t_tree *root, t_exec *exec);
void	command_execute(t_app *self, t_exec *exec);

#endif
