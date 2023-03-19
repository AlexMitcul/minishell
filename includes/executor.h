/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:29:37 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/19 17:37:31 by amitcul          ###   ########.fr       */
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
typedef struct s_io			t_io;
typedef struct s_command	t_command;
typedef struct s_bin_def	t_bin_def;

typedef int (t_bin)(t_app *, char **);

struct	s_bin_def
{
	char	*name;
	t_bin	*builtin;
};

struct s_command
{
	int		argc;
	char	**argv;
	bool	stdin_pipe;
	bool	stdout_pipe;
	int		pipe_read;
	int		pipe_write;
	t_io	*redirect_in;
	t_io	*redirect_out;
};

struct s_io
{
	int		type;
	char	*data;
	t_io	*next;
};

struct s_exec
{
	bool	stdin_pipe;
	bool	stdout_pipe;
	int		pipe_read;
	int		pipe_write;
	t_io	*redirect_in;
	t_io	*redirect_out;
};

int	execute_tree(t_app *self, t_tree *tree);

/* command_funcs.c */
void	command_init(t_tree *root, t_command *command, t_exec exec);
void	command_execute(t_app *self, t_command *command);
void	command_destroy(t_command *command);

int		run(t_app *self, t_command *command);

t_bin	*get_builtin(char *path);

#endif
