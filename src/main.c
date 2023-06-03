/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:10:50 by amitcul           #+#    #+#             */
/*   Updated: 2023/06/03 21:59:03 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/global.h"
#include "../includes/signal_handlers.h"

char	*get_token_type_str(t_token_type type)
{
	if (type == PIPE)
		return "PIPE";
	else if (type == GREAT)
		return "GREAT";
	else if (type == G_GREAT)
		return "G_GREAT";
	else if (type == LESS)
		return "LESS";
	else if (type == L_LESS)
		return "L_LESS";
	else
		return "Word";
}

void print_lexer_list(t_lexer_token *list)
{
	t_lexer_token	*curr;

	curr = list;
	if (!curr)
	{
		printf("Lexer list is empty.\n\n");
		return ;
	}
	while (curr)
	{
		printf("index: %zu\n", curr->index);
		printf("str: %s\n", curr->str);
		printf("token type: %s\n\n", get_token_type_str(curr->token_type));
		printf("token type: %d\n\n", curr->token_type);
		curr = curr->next;
	}
}

 void print_parser_list(t_app *app)
 {
     t_command *command;

     command = app->commands_list;
     if (command == NULL)
     {
         printf("Command list is empty.\n");
         return ;
     }
     while (command)
     {
         printf("Command data:\n");
         int i = 0;
         while (command->str[i])
             printf("%s ", command->str[i++]);
         printf("\nRedirs count: %zu\n", command->redirs_count);
         printf("Heredoc: %s\n", command->heredoc);
         print_lexer_list(command->redirs);
         printf("\n\n");
         command = command->next;
     }
 }

void test_lexer(t_app *app);

void free_2d_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char **envp_dup(char **arr)
{
	char **tab;
	size_t i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	tab = ft_calloc(sizeof(char *), i + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		tab[i] = ft_strdup(arr[i]);
		if (tab[i] == NULL)
		{
			free_2d_array(tab);
			return (tab);
		}
		i++;
	}
	return (tab);
}

int init_app(t_app *app)
{
	app->env_list = NULL;
	app->input = NULL;
	app->lexer_tokens = NULL;
	app->commands_list = NULL;
	app->pipes_count = 0;
	app->reset = false;
	app->pid = NULL;
	app->heredoc = false;
	g_status.stop_heredoc = 0;
	g_status.in_heredoc = 0;
	g_status.in_cmd = 0;
//	parse_envp(app);
	init_signals();
	return (1);
}

int loop(t_app *app)
{
	char	*t;

	app->input = readline(PROMPT);
	t = ft_strtrim(app->input, " ");
	free(app->input);
	app->input = t;
	if (!app->input)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (app->input[0] == '\0')
		return (reset(app));
	add_history(app->input);
	if (!check_quotes(app->input))
		return (ft_error(2, app));
	if (!get_tokens(app))
		return (ft_error(1, app));
	parser(app);
	executor(app);
	reset(app);
	return (1);
}
void	ft_lexerclear(t_lexer_token **lst);
void	ft_simple_cmdsclear(t_command **lst)
{
	t_command 	*tmp;
	t_lexer_token 			*redirections_tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		redirections_tmp = (*lst)->redirs;
		ft_lexerclear(&redirections_tmp);
		if ((*lst)->str)
			free_2d_array((*lst)->str);
		if ((*lst)->heredoc)
			free((*lst)->heredoc);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

int reset(t_app *app)
{
	ft_simple_cmdsclear(&app->commands_list);
	free(app->input);
	if (app->pid)
		free(app->pid);
	free_2d_array(app->paths);
	init_app(app);
	app->reset = true;
	loop(app);
	return (EXIT_SUCCESS);
}

struct s_global g_status = {0, 0, 0, 0};

int	main(int argc, char **argv, char **envp)
{
	t_app	*app;
	int		status;

	if (argc != 1 || argv[1])
		exit(1);
	app = malloc(sizeof(t_app));
	if (!app)
		exit(1);
	app->envp = envp_dup(envp);
	init_app(app);
	status = loop(app);
	return (status);
}
