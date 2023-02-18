/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 22:23:05 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/18 22:31:54 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

#include <stdio.h>

int	lexer(t_dll_item *token_list, char *input);


int main() {
	printf("Hello");

	lexer(NULL, NULL);

	return 0;
}
