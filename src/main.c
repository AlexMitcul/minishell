/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:23:01 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/21 16:30:42 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_prompt(void)
{
	return "$>";
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		input = readline(get_prompt());
		print_dll_list(lexer(input), &print_lexer_token);
		if (input == NULL)
			break;
	}
}
