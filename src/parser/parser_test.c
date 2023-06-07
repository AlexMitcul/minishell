#include "../../includes/minishell.h"
#include "../../includes/error.h"

static void print_commands_list(t_command *list)
{
	while (list)
	{
		char *s = list->str;
		if (!s) {
			printf("Arguments list in empty\n");
		} else {
			while (s) {
				printf("%s ", s);
				s++;
			}
			printf("\n");
		}
		printf("Redirs list: \n");
		// print_lexer_tokens(list->redirs);
		printf("\n\n");
		list = list->next;
	}
}

static void print_parser_info(t_app *app)
{
	printf("	=== Parser Info ===	\n\n");
	printf("Pipes count %d\n", app->pipes_count);
	print_commands_list(app->commands_list);
}

void parser_test(t_app *app)
{
	parser(app);

	print_parser_info(app);
}
