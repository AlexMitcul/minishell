/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 21:11:43 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/18 23:00:27 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define PROMPT "minishell$ " // test

int	g_exit_status = 0;

void	ctrl_d(char *line, t_app **app)
{
	(void)app;
	if (!line)
	{
		rl_clear_history();
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		// terminate(&app); !
		exit(g_exit_status);
	}
}

/* static void	export_display(t_env_list *env_list)
{
	t_env_list	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (tmp->value == NULL)
			printf("declare -x %s\n", tmp->key);
		else
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

static void	sorted_display(t_app *self_dup)
{
	t_env_list	*tmp[2];
	char		*tmp_key_val[2];

	tmp[0] = self_dup->env_list;
	while (tmp[0])
	{
		tmp[1] = tmp[0]->next;
		while (tmp[1])
		{
			if (ft_strncmp(tmp[0]->key, tmp[1]->key, \
				ft_strlen(tmp[0]->key) + ft_strlen(tmp[1]->key)) > 0)
			{
				tmp_key_val[0] = tmp[0]->key;
				tmp_key_val[1] = tmp[0]->value;
				tmp[0]->key = tmp[1]->key;
				tmp[0]->value = tmp[1]->value;
				tmp[1]->key = tmp_key_val[0];
				tmp[1]->value = tmp_key_val[1];
			}
			tmp[1] = tmp[1]->next;
		}
		tmp[0] = tmp[0]->next;
	}
	export_display(self_dup->env_list);
	free_env_list(self_dup); // double free error, investigate!
} */

int	mini_loop(t_app *app)
{
	char	*l;
	char	*ppt;

	sig_config();
	ppt = set_prompt();
	l = readline(ppt);
	free(ppt);
	ctrl_d(l, &app);
	add_history(l);
	app->input = ft_strtrim(l, " ");
	free(l);
	if (!app->input)
		return (mini_perr(PRE, "malloc", 1, 0));
	if (!check_quotes(app->input))
		return (ft_error(2, app));
	if (!get_tokens(app))
		return (ft_error(1, app));
	if (parser(app) != 0 || executor(app) != 0)
		return (g_exit_status);
	// sorted_display(app);
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
		return (mini_perr(PRE, "malloc", 1, 0));
	fill_env_list(app, envp);
	while (1)
		mini_loop(app);
	return (0);
}
