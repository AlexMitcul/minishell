/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 21:11:43 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/13 21:13:07 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define PROMPT "minishell$ " // test

int	g_exit_status = 0;

int	mini_loop(t_app *app) // MAIN
{
	char	*l;

	sig_config();
	// l = readline(set_prompt());
	l = readline(PROMPT); // update
	if (!l)
	{
		// reset(app);
		rl_clear_history();
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(g_exit_status);
	}
	add_history(l);
	app->input = ft_strtrim(l, " ");
	free(l);
	if (!app->input)
		return (mini_perr("minishell: ", "malloc", 1, 0));
	if (!check_quotes(app->input))
		return (ft_error(2, app));
	if (!get_tokens(app))
		return (ft_error(1, app));
	if (parser(app) != 0 || executor(app) != 0)
		return (g_exit_status);
	// reset(app); !!!!!!!!!!!!!!
	return (0);
}

int	main(int argc, char **argv, char **envp) // FINAL
{
	t_app	*app;

	(void)argc;
	(void)argv;
	app = ft_calloc(1, sizeof(t_app));
	if (!app)
		return (mini_perr("minishell: ", "malloc", 1, 0));
	fill_env_list(app, envp);
	while (1)
		mini_loop(app);
	return (0);
}
