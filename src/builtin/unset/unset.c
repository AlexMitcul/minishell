/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenses- <amenses-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 20:02:37 by amenses-          #+#    #+#             */
/*   Updated: 2023/02/25 20:58:21 by amenses-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	argsmatch(char var_name, t_env_list *list)
{
	t_env_list	*t;

	t = list;
	while (list)
	{
		if (!ft_strncmp(var_name, list->key, ft_strlen(var_name)))
			return (1);
		list = list->next;
	}
	list = t;
	return (0);
}

static int argsmatch_1(char var_name, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!ft_strncmp(args[i], var_name, ft_strlen(args[i])))
			return (1);
		i++;
	}
	return (0);
}

static void	remove_env_node(t_app **self)
{
	
}

void	unset(t_app **self, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (argsmatch(args[i], (*self)->env_list))
			remove_env_node(self);
		i++;
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 != '\0' && *s2 != '\0' && n > 0)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int main(void)
{
	printf("%d\n", ft_strncmp("ola", "ola", 3));
	return (0);
}
