

#include "../../includes/expander.h"

char	*handle_single_quotes(char *str, size_t *start);
char    *handle_double_quotes(char *str, size_t *start, t_env_list *list);

bool is_delimeter(char c)
{
    return (c == '\'' || c == '"' || c == '$');
}

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

//static void print_env_list(t_env_list *list)
//{
//    while (list) {
//        printf("%s %s\n", list->key, list->value);
//        list = list->next;
//    }
//}

// static char    *get_env_value(char *key, t_env_list *env_list)
// {
//     t_env_list *tmp;
//     if (!env_list)
//         return (NULL);
//     tmp = env_list;
//     while (tmp)
//     {
//         if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
//             return (tmp->value);
//         tmp = tmp->next;
//     }
//     return (NULL);
// }


// handle $?
char *handle_dollar_sign(char *str, size_t *start, t_env_list *list)
{
    size_t  i;
    size_t  length;
    char *varname;

    (void)list;
    i = *start + 1;
    while (str[i] != '\0' && is_delimeter(str[i]) == false)
        i++;
    length = i - *start - 1;
    varname = ft_substr(str, *start + 1, length);
    // printf("%s\n", varname);
    *start += length + 1;
    return (get_env_value(list, varname));
}

size_t	get_head(char **result, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !is_delimeter(str[i]))
		i++;
	*result = ft_calloc(i + 1, sizeof(char));
    ft_memcpy(*result, str, i);
	return (i);
}

char    *join(char **strs)
{
    size_t total_length;
    size_t i;
    size_t written;
    char *result;

    total_length = 0;
    i = 0;
    while (strs[i] != NULL)
    {
        total_length += ft_strlen(strs[i]);
        i++;
    }
    result = (char *) ft_calloc(total_length + 1, sizeof(char));
    if (!result)
        return (NULL);
    i = 0;
    written = 0;
    while (strs[i] != NULL)
    {
        total_length = ft_strlen(strs[i]);
        ft_memcpy(result + written, strs[i], total_length);
        written += total_length;
        i++;
    }
    return (result);
}

bool is_valid_varname_character(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_')
        return (true);
    return (false);
}

char *try_expand(char *str, t_env_list *list)
{
	char *result;
	char **to_join;
	size_t	result_index;
	size_t	i;

	// check that str exist
    i = 0;
	to_join = ft_calloc(100, sizeof(char *));
	result_index = 0;
	if (!is_delimeter(str[0]))
	{
		char *head = NULL;
		i += get_head(&head, str);
        // printf("head: %s\n", head);
		to_join[result_index] = head;
		result_index++;
	}
	while (str[i])
	{
		if (str[i] == '\'')
			to_join[result_index++] = handle_single_quotes(str, &i);
		else if (str[i] == '"')
			to_join[result_index++] = handle_double_quotes(str, &i, list);
		else if (str[i] == '$')
            to_join[result_index++] = handle_dollar_sign(str, &i, list);
	}
    result = join(to_join);
    free_strs(to_join);
    return (result);
}

char **expand(t_env_list *list, char **strs)
{
    size_t i;
    char *tmp;

    (void)list;
    i = 0;
    while (strs[i] != NULL)
    {
        tmp = try_expand(strs[i], list);
        free(strs[i]);
        strs[i] = tmp;
        i++;
    }
    return (strs);
}

int expander(t_app *app)
{
	t_command *command;
	char **expanded;

	command = app->commands_list;
	while (command)
	{
		expanded = expand(app->env_list, command->str);
		// print_strs(expanded);
		(void)expanded;
		command = command->next;
	}
	return (EXIT_SUCCESS);
}
