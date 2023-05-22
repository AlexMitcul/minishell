/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.c>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:03:45 by amitcul           #+#    #+#             */
/*   Updated: 2023/05/22 13:10:34 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser_error(t_parser_error error, void *data)
{
    (void)error;
    (void)data;
//    return EXIT_FAILURE;
    exit(EXIT_FAILURE);
}