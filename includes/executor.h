/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:29:37 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/19 16:43:12 by amitcul          ###   ########.fr       */
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
typedef struct s_data		t_data;
typedef struct s_command	t_command;

struct s_command
{
	int		argc;
	char	**argv;
	bool	stdin_pipe;
	bool	stdout_pipe;
	int		pipe_read;
	int		pipe_write;
	t_data	*redirect_in;
	t_data	*redirect_out;
};

struct s_data
{
	int				type;
	char			data;
	struct s_data	*next;
};

struct s_exec
{
	bool	in_pipe;
	bool	out_pipe;
	int		read_fd;
	int		write_fd;
	t_data	*in;
	t_data	*out;
};

int	execute_tree(t_app *self, t_tree *tree);

/* command_funcs.c */
// void	command_init(t_tree *root, t_exec *exec);
// void	command_execute(t_app *self, t_exec *exec);

#endif
