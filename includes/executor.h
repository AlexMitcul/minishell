/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:59:30 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/14 19:28:48 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/types.h>
# include <sys/wait.h>
# include "minishell.h"

int		sig_ignore(void);

int		heredoc_sig_config(void); // HEREDOC

int		chld_sig_config(void); // EXEC_UTILS

int		mini_err(char *pre, char *name, char *msg, int exit_status); // EXEC_UTILS

int		mini_perr(char *pre, char *name, int exit_status, int fail); // EXEC_UTILS

void	ft_splitfree(char **str); // EXEC_UTILS

// int		red_out(t_command *cmd, t_lexer_token *red); // REDIRECTOR
int		red_out(t_app *app, t_command *cmd); // REDIRECTOR

// int		red_append(t_command *cmd, t_lexer_token *red); // REDIRECTOR
int		red_append(t_app *app, t_command *cmd); // REDIRECTOR

// int		red_in(t_command *cmd, t_lexer_token *red); // REDIRECTOR
int		red_in(t_app *app, t_command *cmd); // REDIRECTOR

// int		wr_heredoc(t_lexer_token *red); // HEREDOC

// int		red_heredoc(t_command *cmd, t_lexer_token *red); // HEREDOC
int		red_heredoc(t_app *app, t_command *cmd); // HEREDOC

/*  int		set_fd(t_command *cmd, t_lexer_token *red, \
 			int (*f)(t_command*, t_lexer_token*), int io); // EXEC_FDS */
int		set_fd(t_app *app, t_command *cmd, int (*f)(t_app *, t_command *), int io); // EXEC_FDS

// int		redirector(t_command *commands_list); // REDIRECTOR
int		redirector(t_app *app); // REDIRECTOR

int		isbuiltin(char *cmd); // EXEC_BUILTINS

int		bi(t_command *cmd, t_app *app); // EXEC_BUILTINS

int		exec_bi(t_command *cmd, t_app *app); // EXEC_BUILTINS

int		exec_cmd(t_command *cmd, t_app *app); // EXEC_PIPELINE

int		piper(t_command *commands_list); // EXECUTOR

int		waiter(t_command *commands_list); // SUBSHELLS

int		killer(t_command *commands_list); // SUBSHELLS

int		std_dup(t_command *commands_list, int *stdin_dup, int *stdout_dup); // EXEC_FDS

int		std_reset(int stdin_dup, int stdout_dup); // EXEC_FDS

int		exec_ppx(t_app *app); // EXECUTOR

char	*pathsearch(char *cmd, char **paths);  // COMMAND_PATH

// char	*get_env_value(char *key, t_env_list *env_list); // already somewhere

char	*cmdpath(char *cmd, t_env_list *envl); // COMMAND_PATH

int		exec_simple(t_app *app); // EXECUTOR

int		executor(t_app *app); // EXECUTOR

int		env_list_size(t_env_list *env_list); // probaly somewhere else or utils

char	**getenvp(t_env_list *env_list); // UTILS

char	*get_hostname(void); // PROMPT

char	*get_rlpwd(void); // PROMPT

char	*set_prompt(void); // PROMPT

int		mini_loop(t_app *app); // main */

#endif