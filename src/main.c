// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/03/04 19:32:46 by amitcul           #+#    #+#             */
// /*   Updated: 2023/03/21 21:36:25 by amitcul          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/minishell.h"

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

// /* int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	char	*l;

// 	rl_clear_history();
// 	t_app	*app;

// 	app = malloc(sizeof(t_app));
// 	ft_bzero(app, sizeof(t_app));
// 	fill_env_list(app, envp);
// 	while (1)
// 	{
// 		l = readline(set_prompt());
// 		if (l == NULL) // ctrl-D (EOF)
// 		{
// 			// terminate(all) // function to free everything before exiting shell
// 			rl_clear_history();
// 			ft_putstr_fd("exit\n", STDOUT_FILENO);
// 			exit(g_exit_status);
// 		}
// 		add_history(l);


// 		// BUILTINS TEST
// 		if (ft_strncmp(l, "cd", 2) == 0)
// 		{
// 			ft_cd(app, ft_split(l, ' '));
// 		}
// 		if (ft_strncmp(l, "echo", 4) == 0)
// 		{
// 			ft_echo(app, ft_split(l, ' '));
// 		}
// 		if (ft_strncmp(l, "exit", 4) == 0)
// 		{
// 			ft_exit(app, ft_split(l, ' '));
// 		}
// 		if (ft_strncmp(l, "export", 6) == 0)
// 		{
// 			ft_export(app, ft_split(l, ' '));
// 		}
// 		if (ft_strncmp(l, "pwd", 3) == 0)
// 		{
// 			ft_pwd(app, ft_split(l, ' '));
// 		}
// 		if (ft_strncmp(l, "unset", 5) == 0)
// 		{
// 			ft_unset(app, ft_split(l, ' '));
// 		}
// 		if (ft_strncmp(l, "env", 3) == 0)
// 		{
// 			ft_env(app, ft_split(l, ' '));
// 		}
// 		// TEST END

// 		free(l);
// 	}
// 	return (EXIT_SUCCESS);
// } */
