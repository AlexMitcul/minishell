/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:46:32 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/15 18:56:41 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <signal.h>
# include "minishell.h"

int ft_cd(t_app *self, char **args);

int	ft_echo(t_app *self, char **args);

int	ft_env(t_app *self, char **args);

int	ft_exit(t_app *self, char **args);

int	ft_export(t_app *self, char **args);

int	ft_pwd(t_app *self, char **args);

int	ft_unset(t_app *self, char **args);

int	sig_config(void);

char	*get_env_value(t_env_list *env_list, char *key);

int		env_list_size(t_env_list *env_list);

t_app	*env_list_dup(t_env_list *env_list);

#endif