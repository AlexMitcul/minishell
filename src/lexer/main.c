/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 22:23:05 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/19 15:05:56 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

#include <stdio.h>
int		lexer(t_dll_item *, char *);


int main() {
	t_dll_item	*list;

	list = NULL;
	lexer(list, "cat < in > out;");

	return 0;
}
