#include "minishell.h"

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
//		printf("token type: %s\n\n", get_token_type_str(curr->token_type));
        printf("token type: %d\n\n", curr->token_type);
		curr = curr->next;
	}
}

void test_lexer(t_app *app)
{
	app->input = ft_strdup("w > w < w | w >> w <<");
	lexer(app);
	print_lexer_list(app->lexer_tokens);
	for (int i = 0; app->lexer_tokens != NULL; app->lexer_tokens = app->lexer_tokens->next, i++) {
		if (i % 2 == 0 && app->lexer_tokens->token_type == WORD) {
			printf("OK\n");
		} else if (i % 2 == 1 && app->lexer_tokens->token_type != WORD) {
			printf("OK\n");
		} else {
			printf("Error on token %d.\n", i);
		}
	}

	// printf("Test\n");
}

