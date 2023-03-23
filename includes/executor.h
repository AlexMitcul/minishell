/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:29:37 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/23 15:00:17 by amitcul          ###   ########.fr       */
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

# define BUILTINS_COUNT 7

typedef int (t_builtin)(t_app *, char **);

typedef struct s_builtin_def
{
	char		*name;
	t_builtin	*func;
}	t_builtin_def;

typedef struct s_command
{
	int		argc;
	char	**argv;
}	t_command;

void		executor(t_app *self, t_tree *root);

/* command.c */
t_command	*build_command(t_tree *root);
void		free_command(t_command *command);

/* builtins.c */
t_builtin	*is_our_builtin(char *command);
char		*find_builtin_path(t_app *self, char *command_name);

/* executor_utils.c */
void		print_command(t_command *command);

/* run.c */
void	run_builtin(t_app *self, t_command *command);

#endif
