/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:56:42 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/19 16:57:55 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bin	*get_builtin(char *path)
{
	static t_bin_prot	buitins[7] = {
		{"echo", ft_echo},
		{"cd", ft_cd},
		{"pwd", ft_pwd},
		{"export", ft_export},
		{"unset", ft_unset},
		{"env", ft_env},
		{"exit", ft_exit},
	}
	int					i;

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(path, builtins[i].name, ft_strlen(path)) == 0)
			return (builtins[i].builtin);
		i++:
	}
	return (NULL);
}
