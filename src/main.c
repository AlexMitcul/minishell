/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:32:46 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/05 21:23:30 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define PROMPT "$>"

int init_app(t_app *app)
{
	app->env_list = NULL;
	app->input = NULL;
	app->lexer_tokens = NULL;
	app->commands_list = NULL;
	app->pipes_count = 0;
	app->reset = false;
	app->pid = NULL;
	app->heredoc = false;
	// global_variable_or_struct_init???
//	parse_envp(app);
	// init_signals();
	return (1);
}

int loop(t_app *app);
int reset(t_app *app)
{
	/*
	reset and clear all structs
	*/
	loop(app);
	return (EXIT_SUCCESS);
}

int loop(t_app *app)
{
	char	*t;

	app->input = readline(PROMPT);
	t = ft_strtrim(app->input, " ");
	free(app->input);
	app->input = t;
	if (!app->input)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (app->input[0] == '\0')
		return (reset(app));
	add_history(app->input);
	if (!check_quotes(app->input))
		return (ft_error(2, app));
	if (!get_tokens(app))
		return (ft_error(1, app));
	parser(app);
	// executor(app);
	reset(app);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_app	*app;
	int		status;

	(void)envp;
	if (argc != 1 || argv[1])
		exit(1);
	app = malloc(sizeof(t_app));
	if (!app)
		exit(1);
	// app->envp = envp_dup(envp);
	init_app(app);
	status = loop(app);
	return (status);
}

// int	g_exit_status;

// char	*get_hostname(void)
// {
// 	char	*tmp;
// 	int		fd;
// 	char	*host;

// 	fd = open("/etc/hostname", 00);
// 	if (fd == -1)
// 		return (NULL);
// 	tmp = get_next_line(fd);
// 	if (tmp == NULL)
// 		return (NULL);
// 	close(fd);
// 	host = ft_substr(tmp, 0, ft_strchr(tmp, '.') - tmp);
// 	free(tmp);
// 	return (host);
// }

// char	*get_rlpwd(void)
// {
// 	char	*rlpwd;
// 	char	*home;
// 	char	*tmp;

// 	rlpwd = getcwd(NULL, 0);
// 	if (rlpwd == NULL)
// 		return (NULL);
// 	home = ft_strjoin(getenv("HOME"), "/");
// 	if (home == NULL)
// 		home = ft_strdup("/");
// 	if (ft_strncmp(rlpwd, home, ft_strlen(home)) == 0)
// 	{
// 		tmp = ft_substr(rlpwd, ft_strlen(home) - 1, ft_strlen(rlpwd));
// 		free(rlpwd);
// 		free(home);
// 		rlpwd = ft_strjoin("~", tmp);
// 		free(tmp);
// 		return (rlpwd);
// 	}
// 	return (NULL);
// }

// char	*set_prompt(void)
// {
// 	char	*host;
// 	char	*rlpwd;
// 	char	*ppt;
// 	char	*tmp;

// 	host = get_hostname();
// 	rlpwd = get_rlpwd();
// 	ppt = ft_strjoin(getenv("USER"), "@");
// 	tmp = ppt;
// 	ppt = ft_strjoin(ppt, host);
// 	free(tmp);
// 	tmp = ppt;
// 	ppt = ft_strjoin(ppt, ":");
// 	free(tmp);
// 	tmp = ppt;
// 	ppt = ft_strjoin(ppt, rlpwd);
// 	free(tmp);
// 	tmp = ppt;
// 	ppt = ft_strjoin(ppt, "$ ");
// 	free(tmp);
// 	free(host);
// 	free(rlpwd);
// 	return (ppt);
// }

/* int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char	*l;

	rl_clear_history();
	t_app	*app;

	app = malloc(sizeof(t_app));
	ft_bzero(app, sizeof(t_app));
	fill_env_list(app, envp);
	while (1)
	{
		l = readline(set_prompt());
		if (l == NULL) // ctrl-D (EOF)
		{
			// terminate(all) // function to free everything before exiting shell
			rl_clear_history();
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			exit(g_exit_status);
		}
		add_history(l);


		// BUILTINS TEST
		if (ft_strncmp(l, "cd", 2) == 0)
		{
			ft_cd(app, ft_split(l, ' '));
		}
		if (ft_strncmp(l, "echo", 4) == 0)
		{
			ft_echo(app, ft_split(l, ' '));
		}
		if (ft_strncmp(l, "exit", 4) == 0)
		{
			ft_exit(app, ft_split(l, ' '));
		}
		if (ft_strncmp(l, "export", 6) == 0)
		{
			ft_export(app, ft_split(l, ' '));
		}
		if (ft_strncmp(l, "pwd", 3) == 0)
		{
			ft_pwd(app, ft_split(l, ' '));
		}
		if (ft_strncmp(l, "unset", 5) == 0)
		{
			ft_unset(app, ft_split(l, ' '));
		}
		if (ft_strncmp(l, "env", 3) == 0)
		{
			ft_env(app, ft_split(l, ' '));
		}
		// TEST END

		free(l);
	}
	return (EXIT_SUCCESS);
} */
