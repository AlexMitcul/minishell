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

#include "parser.h"

typedef struct	s_parser
{
	t_lexer_token	*lexer_list;
	t_lexer_token	*redirs;
	int				redirs_count;
	struct s_app	*app;
}	t_parser;

typedef struct s_command
{
	char				**str;
	// int					(*builtin);
	int					redirs_count;
	char				*filename;
	t_lexer_token		*redirs;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

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

typedef enum s_parser_error
{
	SYNTAX_ERROR = 42,
	MEMORY_ERROR
}	t_parser_error;

int	parser_error(t_parser_error error, void *data)
{
	(void)error;
	(void)data;
	return EXIT_FAILURE;
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

// int	add_new_redir(t_lexer_token *tmp, t_parser *parser)
// {
// 	t_lexer_token	*curr;
// 	int				i;
// 	int				j;
// }

void	remove_redir(t_parser *parser)
{
	t_lexer_token	*tmp;

	tmp = parser->lexer_list;
	while (tmp && tmp->token_type == 0)
		tmp = tmp->next;
	if (!tmp || tmp->token_type == PIPE)
		return ;
	if (!tmp->next)
		parser_error(SYNTAX_ERROR, NULL);
	if (tmp->next->token_type)
		parser_error(0, 0); //! handle this error
	// if (tmp->token_type >= GREAT && tmp->token_type <= L_LESS)
	// 	add_new_redir(tmp, parser);
	remove_redir(parser);
}

size_t	count_args(t_lexer_token *list)
{
	size_t			i;

	i = 0;
	while (list && list->token_type != PIPE)
	{
		if (list->index >= 0)
			i += 1;
		list = list->next;
	}
	return (i);
}

t_command	*init_command(t_parser *parser)
{
	char			**str;
	int				index;
	size_t			args_size;
	t_lexer_token	*tmp;

	index = 0;
	remove_redir(parser);
	args_size = count_args(parser->lexer_list);
	str = ft_calloc(args_size + 1, sizeof(char *));
	if (!str)
		parser_error(MEMORY_ERROR, NULL);
	tmp = parser->lexer_list;
	while (args_size > 0)
	{
		if (tmp->str)
		{
			str[index++] = ft_strdup(tmp->str);
			lexerdel_one(&parser->lexer_list, tmp->index);
			tmp = parser->lexer_list;
		}
		args_size -= 1;
	}
	return (create_simple_command(str, parser->redirs_count, parser->redirs));
}

static void	push_back(t_command **list, t_command *new)
{
	t_command	*tmp;

	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

int	parser(t_app *app)
{
	t_command	*command;
	t_parser	*parser;

	if (app->lexer_tokens->token_type == PIPE)
		return parser_error(SYNTAX_ERROR, &PIPE);
	app->commands = NULL;
	count_pipes(app);
	while (app->lexer_tokens)
	{
		if (app->lexer_tokens && app->lexer_tokens->token_type == PIPE)
			lexerdel_one();
		// if () handle pipe error
		parser = init_parser(app);
		command = init_command(parser);
		if (!command)
			parser_error();
		if (!app->commads_list)
			app->commands_list = command;
		else
			push_back(app->commands_list, command);
		app->lexer_list = parser->lexer_list;
	}
	return (EXIT_SUCCESS);
}
