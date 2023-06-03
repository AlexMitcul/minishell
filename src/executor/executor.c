/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:34:55 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/03 21:36:51 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/global.h"

void	free_2d_array(char **arr);
int		execute(t_app *app);

t_command	*pre_expand(t_app *app, t_command *command)
{
	t_lexer_token	*token;

	command->str = expander(app, command->str);
	token = command->redirs;
	while (command->redirs)
	{
		if (command->redirs->token_type != L_LESS)
			command->redirs->str = expander_str(app, command->redirs->str);
		command->redirs = command->redirs->next;
	}
	command->redirs = token;
	return (command);
}

char	*join_split_str(char **splitted, char *new_str)
{
	char	*tmp;
	char	*space;
	int		i;

	tmp = ft_strdup(splitted[0]);
	i = 1;
	while (splitted[i])
	{
		new_str = tmp;
		space = ft_strjoin(new_str, " ");
		free(new_str);
		tmp = ft_strjoin(space, splitted[i]);
		free(space);
		i++;
	}
	new_str = tmp;
	return (new_str);
}

char	**resplit_str(char **arr)
{
	char	**result;
	char	*joined;

	joined = join_split_str(arr, NULL);
	free_2d_array(arr);
	result = ft_split(joined, ' ');
	free(joined);
	joined = join_split_str(result, NULL);
	free_2d_array(result);
	result = ft_split(joined, ' ');
	free(joined);
	return (result);
}

int	not_found(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}

int	find_command(t_command *command, t_app *app)
{
	int		i;
	char	*command_name;

	i = 0;
	command->str = resplit_str(command->str);
	if (!access(command->str[0], F_OK))
		execve(command->str[0], command->str, app->envp);
	while (app->paths[i])
	{
		command_name = ft_strjoin(app->paths[i], command->str[0]);
		if (!access(command_name, F_OK))
			execve(command_name, command->str, app->envp);
		free(command_name);
		i++;
	}
	return (not_found(command->str[0]));
}

int	check_redirs(t_command *command)
{
	t_lexer_token	*token;

	token = command->redirs;
	while (command->redirs)
	{
		if (command->redirs->token_type == LESS)
		{
			if (handle_infile(command->redirs->str))
				return (EXIT_FAILURE);
		}
		else if (command->redirs->token_type == GREAT
			|| command->redirs->token_type == G_GREAT)
		{
			if (handle_outfile(command->redirs))
				return (EXIT_FAILURE);
		}
		else if (command->redirs->token_type == L_LESS)
		{
			if (handle_infile(command->heredoc))
				return (EXIT_FAILURE);
		}
		command->redirs = command->redirs->next;
	}
	command->redirs = token;
	return (EXIT_SUCCESS);
}

void	handle_command(t_command *command, t_app *app)
{
	int	status;

	status = 0;
	if (command->redirs)
		if (check_redirs(command))
			exit(1);
	if (command->builtin != NULL)
	{
		status = command->builtin(app, command->str);
		exit(status);
	}
	else if (command->str[0][0] != '\0')
		status = find_command(command, app);
	exit(status);
}

void	simple_command(t_app *app, t_command *command)
{
	int	pid;
	int	status;

	command = app->commands_list;
	app->commands_list = pre_expand(app, command);
	if (command->builtin == ft_cd || command->builtin == ft_exit
		|| command->builtin == ft_export || command->builtin == ft_unset)
	{
		g_status.error_num = command->builtin(app, command->str);
		return ;
	}
	send_heredoc(app, command);
	pid = fork();
	if (pid < 0)
		ft_error(5, app);
	if (pid == 0)
		handle_command(command, app);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_status.error_num = WEXITSTATUS(status);
}

int	executor(t_app *app)
{
	signal(SIGQUIT, sigquit_handler);
	g_status.in_cmd = 1;
	if (app->pipes_count == 0)
		simple_command(app, app->commands_list);
	else
	{
		app->pid = ft_calloc(sizeof(int), app->pipes_count + 2);
		if (!app->pid)
			return (ft_error(1, app));
		execute(app);
	}
	g_status.in_cmd = 0;
	return (EXIT_SUCCESS);
}

void	dup_cmd(t_command *cmd, t_app *app, int end[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		ft_error(4, app);
	close(end[0]);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		ft_error(4, app);
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	handle_command(cmd, app);
}

int	try_fork(t_app *app, int end[2], int fd_in, t_command *command)
{
	static int	i = 0;

	if (app->reset == true)
	{
		i = 0;
		app->reset = false;
	}
	app->pid[i] = fork();
	if (app->pid[i] < 0)
		ft_error(5, app);
	if (app->pid[i] == 0)
		dup_cmd(command, app, end, fd_in);
	i++;
	return (EXIT_SUCCESS);
}

int	check_fd_heredoc(t_app *app, int end[2], t_command *cmd)
{
	int	fd_in;

	if (app->heredoc)
	{
		close(end[0]);
		fd_in = open(cmd->heredoc, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

int	pipe_wait(int *pid, int amount)
{
	int	i;
	int	status;

	i = 0;
	while (i < amount)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		g_status.error_num = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}

t_command	*simple_command_first(t_command *map)
{
	int	i;

	i = 0;
	if (!map)
		return (NULL);
	while (map->prev != NULL)
	{
		map = map->prev;
		i++;
	}
	return (map);
}

int	execute(t_app *app)
{
	int	end[2];
	int	fd_in;

	fd_in = STDIN_FILENO;
	while (app->commands_list)
	{
		app->commands_list = pre_expand(app, app->commands_list);
		if (app->commands_list->next)
			pipe(end);
		send_heredoc(app, app->commands_list);
		try_fork(app, end, fd_in, app->commands_list);
		close(end[1]);
		if (app->commands_list->prev)
			close(fd_in);
		fd_in = check_fd_heredoc(app, end, app->commands_list);
		if (app->commands_list->next)
			app->commands_list = app->commands_list->next;
		else
			break ;
	}
	pipe_wait(app->pid, app->pipes_count);
	app->commands_list = simple_command_first(app->commands_list);
	return (0);
}
