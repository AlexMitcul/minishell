/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:47:01 by amitcul           #+#    #+#             */
/*   Updated: 2023/05/21 12:13:08 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

# include <stdbool.h>
# include <limits.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "lexer.h"
# include "parser.h"
# include "utils.h"
# include "builtins.h"
# include "expander.h"
# include "executor.h"
# include "structs.h"
# include "error.h"
# include "signal_handlers.h"

//typedef struct s_status
//{
//
//} t_status;
//
//t_status g_status;

typedef struct s_app		t_app;
typedef struct s_env_list	t_env_list;

# define PROMPT "$> "

# define HEREDOC_MSG "\033[1;34m> \033[0m"

/* utils.c */
void	fill_env_list(t_app *self, char **envp);
void	free_env_list(t_app *self);
void	remove_list_item_by_key(t_app *self, char *key);
char	*find_list_value_by_key(t_env_list *list, char *key);
void	free_array(char **arr);

int parser(t_app *app);



int reset(t_app *app);

#endif
