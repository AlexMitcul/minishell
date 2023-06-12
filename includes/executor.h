/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:59:30 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/12 18:38:10 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/types.h>
# include <sys/wait.h>

int	child_sig_config(void);
int	mini_err(char *pre, char *name, char *msg, int exit_status);
int	mini_perr(char *pre, char *name, int exit_status, int fail);

#endif