/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:39:39 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/13 23:46:49 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

static int	set_option(char ** args)
{
	int i;
	int	j;

	i = 1;
	while (args[i])
	{
		if (ft_strncmp(args[i], "-n", 2) == 0)
		{
			// printf("args[%d] = %s\n", i, args[i]);
			j = 1;
			while (args[i][j])
			{
				if (args[i][j] != 'n')
					return (i);
				j++;
			}
			i++;
		}
		else
			return (i);
	}
	return (i);
}

int	ft_echo(t_app *self, char **args)
{
	int	i;
	int	n_flag;

	(void)self;
	// i = 1;
	// n_flag = 0;
	// if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	// {
	// 	n_flag = 1;
	// 	i++;
	// }
	n_flag = set_option(args);
	printf("n_flag: %d\n", n_flag);
	i = n_flag;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (n_flag == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_exit_status = 0;
	return (g_exit_status);
}

/* int	main(int argc, char **argv, char **envp)
{
	t_app	*app;

	(void)argc;
	app = malloc(sizeof(t_app));
	fill_env_list(app, envp);
	ft_echo(argv + 1);
	free_env_list(app);
	free(app);
	return (EXIT_SUCCESS);
} */
