/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:23:01 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/25 19:32:00 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	*get_prompt(void)
// {
// 	return "$>";
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;

// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	while (1)
// 	{
// 		input = readline(get_prompt());
// 		print_dll_list(lexer(input), &print_lexer_token);
// 		if (input == NULL)
// 			break;
// 	}
// }


int main(int argc, char **argv, char **envp)
{
	t_app	*self;

	(void)argc;
	(void)argv;

	self = ft_calloc(sizeof(t_app), 1);
	fill_env_list(self, envp);
	while (self->env_list)
	{
		printf("%s=%s\n", self->env_list->key, self->env_list->value);
		self->env_list = self->env_list->next;
	}
	return (0);
}
