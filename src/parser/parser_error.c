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


char *get_redirect_str(t_lexer_token *token)
{
    t_token_type type;

    type = token->token_type;
    if (type == PIPE)
        return "|";
    else if (type == GREAT)
        return ">";
    else if (type == G_GREAT)
        return ">>";
    else if (type == LESS)
        return "<";
    else if (type == L_LESS)
        return "<<";
    else
        return "";
}

void	parser_error(t_parser_error error, t_app *app, t_parser *parser,
                     t_lexer_token *curr)
{
    (void) app;
    (void) parser;
    (void) curr;
    if (error == SYNTAX_ERROR)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token '", STDERR_FILENO);
        ft_putstr_fd(curr->str, STDERR_FILENO);
        ft_putstr_fd("'\n", STDERR_FILENO);
    }
    else if (error == REDIRECT)
    {
        ft_putstr_fd("minishell: syntax error near unexpected token '", STDERR_FILENO);
        ft_putstr_fd(get_redirect_str(curr), STDERR_FILENO);
        ft_putstr_fd("'\n", STDERR_FILENO);
    }
    exit(EXIT_FAILURE);
}