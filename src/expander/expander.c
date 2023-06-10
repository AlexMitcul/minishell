

#include "../../includes/expander.h"

void print_strs(char **strs)
{
	size_t i;

	i = 0;
	if (strs == NULL || strs[i] == NULL)
	{
		printf("Is empty.\n");
		return ;
	}
	while (strs[i])
	{
		printf("%s ", strs[i]);
		i++;
	}
	printf("\n");
}

size_t count_strings(char **strs)
{
	size_t	count;

	count = 0;
	while (strs[count])
		count++;
	return (count);
}

void free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

// 'echo'
// ^    ^
// 012345

char	*handle_single_quotes(char *str, size_t *start)
{
	size_t i;
	size_t len;
	char *result;

	i = *start + 1;
	while (str[i] != '\0' && str[i] != '\'')
		i++;
	len = *start - i;
	result = (char *)ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(result, str + 1, len);
	*start += len;
	return (result);
}

// 'echo'

bool is_delimeter(char c)
{
	return (c == '\'' || c == '"' || c == '$');
}

size_t	get_head(char **result, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !is_delimeter(str[i]))
		i++;
	*result = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(*result, str, i);
	return (i);
}

char *try_expand(char *str)
{
	char *result;
	char **to_join;
	size_t	result_index;
	size_t	i;

	// check that str exist
	to_join = ft_calloc(100, sizeof(char *));
	result_index = 0;
	if (!is_delimeter(str[0]))
	{
		char *head = NULL;
		i += get_head(&head, str);
		printf("head: %s\n", head);
		to_join[result_index] = head;
		result_index++;
	}
	while (str[i])
	{
		if (str[i] == '\'')
			to_join[result_index++] = handle_single_quotes(str, &i);
//		else if (str[i] == '"')
//			i += handle_double_quotes(str, i);
//		else if (str[i] == '$')
//			i += handle_dollar_sign(str[i])
	}

}

char **expand(t_env_list *list, char **strs)
{


}

int expander(t_app *app)
{
	t_command *command;
	char **expanded;

	command = app->commands_list;
	while (command)
	{
		expanded = expand(app->env_list, command->str);
		print_strs(expanded);
		command = command->next;
	}
	return (EXIT_SUCCESS);
}
