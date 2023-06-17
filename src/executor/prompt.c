/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 20:35:23 by amenses-          #+#    #+#             */
/*   Updated: 2023/06/17 23:51:00 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

char	*get_hostname(void)
{
	char	*tmp;
	int		fd;
	char	*host;

	fd = open("/etc/hostname", 00);
	if (fd == -1)
		return (NULL);
	tmp = get_next_line(fd);
	if (tmp == NULL)
		return (NULL);
	close(fd);
	host = ft_substr(tmp, 0, ft_strchr(tmp, '.') - tmp);
	free(tmp);
	return (host);
}

char	*get_rlpwd(void) // review !
{
	char	*rlpwd;
	char	*home;
	char	*tmp;

	rlpwd = getcwd(NULL, 0);
	if (rlpwd == NULL)
		return (NULL);
	home = ft_strjoin(getenv("HOME"), "/");
	if (home == NULL)
		home = ft_strdup("/");
	if (ft_strncmp(rlpwd, home, ft_strlen(home)) == 0)
	{
		tmp = ft_substr(rlpwd, ft_strlen(home) - 1, ft_strlen(rlpwd));
		free(rlpwd);
		free(home);
		rlpwd = ft_strjoin(YELB "~", tmp);
		free(tmp);
		return (rlpwd);
	}
	return (NULL);
}

char	*set_prompt(void)
{
	char	*host;
	char	*rlpwd;
	char	*ppt[2];

	host = get_hostname();
	rlpwd = get_rlpwd();
	ppt[0] = ft_strjoin(getenv("USER"), "@");
	ppt[1] = ppt[0];
	ppt[0] = ft_strjoin(ppt[0], host);
	free(ppt[1]);
	ppt[1] = ppt[0];
	ppt[0] = ft_strjoin(ppt[0], ":");
	free(ppt[1]);
	ppt[1] = ppt[0];
	ppt[0] = ft_strjoin(ppt[0], rlpwd);
	free(ppt[1]);
	ppt[1] = ppt[0];
	ppt[0] = ft_strjoin(ppt[0], "$ " DFT);
	free(ppt[1]);
	ppt[1] = ppt[0];
	ppt[0] = ft_strjoin(BLUEB, ppt[0]);
	free(ppt[1]);
	free(host);
	free(rlpwd);
	return (ppt[0]);
}
