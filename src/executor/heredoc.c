/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 22:20:09 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/14 22:27:41 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

static char	*rm_quotes(char *str)
{
	char	*del;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] != '\"' && str[i] != '\'')
			len++;
	}
	if (len == 0)
		return (ft_strdup(""));
	del = ft_calloc(len + 1, sizeof(char));
	if (!del)
		return (NULL);
	while (len > 0)
	{
		if (str[--i] != '\"' && str[i] != '\'')
			del[--len] = str[i];
	}
	return (del);
}

static char	*get_env_value(char *key, t_env_list *env_list)
{
	t_env_list	*tmp;

	if (!env_list)
		return (NULL);
	tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	hd_expand(char *l, t_env_list *envl, int x, int fd) // !
{
	char	*tmp;
	int		i;
	char	*m;
	char	*key;

	tmp = ft_strchr(l, '$');
	if (!tmp || x > 0)
	{
		ft_putendl_fd(l, fd);
		return ;
	}
	m = l;
	while (m)
	{
		if (!tmp)
		{
			ft_putendl_fd(m, fd);
			return ;
		}
		while (m && m != tmp)
		{
			ft_putchar_fd(*m, fd);
			m++;
		}
		i = 0;
		if (!ft_isalpha(tmp[++i]) && tmp[i] != '_')
		{
			tmp = ft_strchr(tmp + 1, '$');
			continue ;
		}
		while (1)
		{
			if (!tmp[i] || (!ft_isalnum(tmp[i]) && tmp[i] != '_'))
			{
				key = ft_substr(tmp, 1, i - 1);
				ft_putstr_fd(get_env_value(key, envl), fd);
				free(key);
				m = m + i;
				tmp = ft_strchr(tmp + 1, '$');
				break ;
			}
			else
				i++;
		}
	}
}

// static int	wr_heredoc(t_lexer_token *red)
static int	wr_heredoc(t_app *app, t_lexer_token *red)
{
	char	*l;
	int		fd;
	char	*del;

	fd = open("tmp_XmXiXnXiXsXhXeXlXl", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		exit(mini_perr("minishell: ", red->str, 1, 0));
	del = rm_quotes(red->str);
	if (!del)
		exit(mini_perr("minishell: ", "malloc", 1, 0));
	while (1)
	{
		l = readline(">");
		if (ft_strncmp(l, del, ft_strlen(del) + 1) == 0)
			break ;
		hd_expand(l, app->env_list, ft_strlen(red->str) - ft_strlen(del), fd);
		free(l);
	}
	free(del);
	free(l);
	close(fd);
	exit(0);
}

// int	red_heredoc(t_command *cmd, t_lexer_token *red)
int	red_heredoc(t_app *app, t_command *cmd)
{
	pid_t	pid;
	int		fd;

	(void)app;
	pid = fork();
	if (pid == 0)
	{
		heredoc_sig_config();
		// wr_heredoc(red);
		wr_heredoc(app, cmd->redirs);
	}
	else if (pid < 0)
		return (mini_perr("minishell: ", "fork", 1, -1));
	sig_ignore();
	waitpid(pid, &g_exit_status, 0);
	if (WEXITSTATUS(g_exit_status) != 0)
		return (-1);
	sig_config();
	fd = open("tmp_XmXiXnXiXsXhXeXlXl", O_RDONLY);
	if (fd == -1 || unlink("tmp_XmXiXnXiXsXhXeXlXl") == -1)
		mini_perr("minishell:", "here_doc", 1, 0);
	return (fd);
}
