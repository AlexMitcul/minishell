
#include "../../includes/expander.h"

// dollar\$first' part'"i\'m = $USER status = $?code"'end 'part

// result = [00000000000]
// strs = ["aaa", "bb", "fffff"]
/*
 * result = [aaa00000000]
 * result = [aaabb000000]
 * result = [aaabbfffff0]
 */
static char *strings_join(char **strs)
{
	char *result;
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	while (strs[i])
		count += ft_strlen(strs[i++]);
	result = (char *) ft_calloc(count + 1, sizeof(char));
	count = 0;
	i = 0;
	while (strs[count])
	{
		ft_memcpy(result + i, strs[count], ft_strlen(strs[count]));
		i += ft_strlen(strs[count]);
		free(strs[count]);
		count++;
	}
	free(strs);
	return (result);
}

size_t expand_plain_text(char *str, size_t start, char **line)
{
	char *result;

	result = ft_calloc(2, sizeof(char));
	result[0] = str[start];
	*line = result;
	return (start + 1);
}

size_t expand_backslash(char *str, size_t start, char **line)
{
	char *result;

	result = ft_calloc(2, sizeof(char));
	result[0] = str[start + 1];
	*line = result;
	return (start + 2);
}

bool is_valid_to_expand_from_double_quotes(char *str, size_t i)
{
	if (str[i] == '\\' && str[i + 1] && str[i + 1] == '"')
		return (true);
	if (str[i] == '\\' && str[i + 1] && str[i + 1] == '$')
		return (true);
	if (str[i] == '\\' && str[i + 1] && str[i + 1] == '\\')
		return (true);
	return (false);
}

size_t expand_double_quotes(char *str, size_t start, char **line, t_env_list *list)
{
	char **result;
	char *tmp;
	size_t curr_index;
	size_t i;

	result = (char **) ft_calloc(ft_strlen(str) + 1, sizeof(char *));
	curr_index = 0;
	i = start + 1;
	while (str[i] && str[i] != '"')
	{
		tmp = NULL;
		if (is_valid_to_expand_from_double_quotes(str, i))
			i = expand_backslash(str, i, &tmp);
		else if (str[i] == '$')
			i = expand_dollar_sign(str, i, &tmp, list);
		else
			i = expand_plain_text(str, i, &tmp);
		if (tmp)
		{
			result[curr_index++] = ft_strdup(tmp);
			free(tmp);
		}
	}
	*line = strings_join(result);
	return (i);
}

static char *expand_string(char *str, t_env_list *list)
{
	char **result;
	char *line;
	size_t	curr_index;
	size_t	i;

	curr_index = 0;
	result = (char **) ft_calloc(ft_strlen(str) + 1, sizeof(char *));
	line = NULL;
	i = 0;
	// prefix
	while (str[i])
	{
		if (str[i] == '\\')
			i = expand_backslash(str, i, &line);
		else if (str[i] == '\'')
			i = expand_single_quotes(str, i, &line); // !
		else if (str[i] == '"')
			i = expand_double_quotes(str, i, &line, list);
		else if (str[i] == '$')
			i = expand_dollar_sign(str, i, &line, list);
		else
			i = expand_plain_text(str, i, &line);
		result[curr_index++] = ft_strdup(line);
		if (line)
			free(line);
	}
    return (strings_join(result));
}

static char **expand_all_strings(char **strs, t_env_list *list)
{
    char **result;
    size_t curr_string;
    size_t index;

    if (!strs)
        return (NULL);
    // can I do that?
    result = (char **) ft_calloc(100, sizeof(char *));
    if (!result)
        return (NULL);
    index = 0;
    curr_string = 0;
    while (strs[curr_string])
        result[index++] = expand_string(strs[curr_string++], list);
    return (result);
}

static void expand(t_command *cmd, t_env_list *list)
{
    size_t i;
    char **expanded;

    if (!cmd->str)
        return ;
    i = 0;
    expanded = NULL;
    while (cmd->str[i])
    {
        expanded = expand_all_strings(cmd->str, list);
        if (expanded != NULL)
        {
            free_strs(cmd->str);
            cmd->str = expanded;
        }
        i++;
    }
}

int expander(t_app *app)
{
    t_command *cmd;

    cmd = app->commands_list;
    if (!cmd)
        return (EXIT_SUCCESS);
    while (cmd)
    {
        expand(cmd, app->env_list);
        cmd = cmd->next;
    }
//	printf("%s\n", expand_dollar_sign("$?", 0, app->env_list));
//	printf("%s\n", expand_single_quotes(cmd->str[1], 0));
//	return (EXIT_FAILURE); // ! Just for debug
    return (EXIT_SUCCESS);
}