/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:46:32 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/13 20:54:53 by amenses-         ###   ########.fr       */
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

#endif