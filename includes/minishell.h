/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:47:01 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/05 15:53:03 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

# include <stdbool.h>
# include <limits.h>
# include <stdio.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "lexer.h"
# include "parser.h"
# include "utils.h"
# include "executor.h"

# define BUILTINS_COUNT 7

typedef struct s_app		t_app;
typedef struct s_tree		t_tree;
typedef struct s_parser		t_parser;
typedef struct s_token		t_token;
typedef struct s_lexer		t_lexer;
typedef struct s_env_list	t_env_list;
// typedef struct s_command	t_command;
typedef struct s_exec		t_exec;

struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
};

struct s_app
{
	t_env_list	*env_list;
	char		**envp;
};

void	fill_env_list(t_app *self, char **envp);
void	free_env_list(t_app *self);
void	remove_list_item_by_key(t_app *self, char *key);

/* builtins */
int		ft_cd(t_app *self, char **args);
int		ft_echo(char **args); // !
int		ft_env(t_app **self, char **args);
int		ft_exit(t_app *self, char **args);
int		ft_export(t_app **self, char **args);
int		ft_pwd(t_app *self, char **args);
int		ft_unset(t_app **self, char **args);

#endif
