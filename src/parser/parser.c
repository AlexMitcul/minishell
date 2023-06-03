/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:13:05 by amitcul           #+#    #+#             */
/*   Updated: 2023/05/21 12:22:27 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

void	count_pipes(t_app *app)
{
	t_lexer_token	*tmp;

	tmp = app->lexer_tokens;
	app->pipes_count = 0;
	while (tmp)
	{
		if (tmp->token_type == PIPE)
			app->pipes_count += 1;
		tmp = tmp->next;
	}
}

t_parser	*init_parser(t_app *app)
{
	t_parser	*parser;

	parser = (t_parser *) malloc(sizeof(t_parser));
	parser->app = app;
	parser->lexer_list = app->lexer_tokens;
	parser->redirs = NULL;
	parser->redirs_count = 0;
	return (parser);
}

int parser(t_app *app)
{
    t_parser *parser;
    t_command *command;

    parser = NULL;
    command = NULL;
    if (app->lexer_tokens->token_type == PIPE)
        parser_error(REDIRECT, app, parser, app->lexer_tokens);
    count_pipes(app);
    while (app->lexer_tokens)
    {
        if (app->lexer_tokens->token_type == PIPE)
            delete_node_by_index(&app->lexer_tokens, app->lexer_tokens->index);
        if (app->lexer_tokens->token_type == PIPE)
            parser_error(REDIRECT, app, parser, app->lexer_tokens);
        parser = init_parser(app);
        command = get_command(parser);
        if (!command)
            parser_error(PLACEHOLDER, NULL, 0,0);
        add_command_to_list(app, command);
        app->lexer_tokens = parser->lexer_list;
    }
    return (EXIT_SUCCESS);
}








