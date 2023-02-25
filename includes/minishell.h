/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:47:01 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/25 20:58:38 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

# include <stdbool.h>
# include <limits.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "lexer.h"
# include "utils.h"

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_app
{
	t_env_list	*env_list;
	char		**envp;
}	t_app;

void	fill_env_list(t_app *self, char **envp);
void	free_env_list(t_app *self);

#endif
