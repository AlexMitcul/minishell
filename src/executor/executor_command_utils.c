/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:44:57 by amitcul           #+#    #+#             */
/*   Updated: 2023/03/22 12:53:12 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void	print_command(t_command *command)
{
	int	i;

	printf("Command | argc = %d\n", command->argc);
	i = 0;
	while (i < command->argc)
	{
		printf("%d: %s\n", i, command->argv[i]);
		i++;
	}
}
