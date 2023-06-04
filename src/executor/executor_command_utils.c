/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:44:57 by amitcul           #+#    #+#             */
/*   Updated: 2023/04/10 17:18:32 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void	print_command(t_command *command)
{
	int	i;

	if (!command)
	{
		printf("== Command is NULL ==\n");
		return ;
	}
	printf("Command | argc = %d\n", command->argc);
	i = 0;
	while (i < command->argc)
	{
		printf("%d: %s\n", i, command->argv[i]);
		i++;
	}
}
