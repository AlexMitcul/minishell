/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:46:32 by amenses-          #+#    #+#             */
/*   Updated: 2023/03/22 14:56:14 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <signal.h>

int	ft_cd(t_app *self, char **args);

int	ft_echo(t_app *self, char **args);

int	ft_env(t_app *self, char **args);

int	ft_exit(t_app *self, char **args);

int	ft_export(t_app *self, char **args);

int	ft_pwd(t_app *self, char **args);

int	ft_unset(t_app *self, char **args);

int	sig_config(void);

#endif
