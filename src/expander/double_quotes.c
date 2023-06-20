
#include "../../includes/expander.h"




// echo "$PATH || $PATH"

char *handle_dollar_sign(char *str, size_t *start, t_env_list *list);

//static bool is_space(char c)
//{
//    // check for expansion delimeters
//    return (c == ' ');
//}

static void free_join_array(char **strs, size_t count)
{
    size_t i;

	if (!strs || !(*strs))
		return ;
    i = 0;
    while (i < count)
    {
		if (strs[i])
        	free(strs[i]);
        i++;
    }
    free(strs);
}

static char    *join(char **strs, size_t count)
{
    size_t total_length;
    size_t i;
    size_t written;
    char *result;

    total_length = 0;
    i = 0;
    while (i < count)
    {
		if (strs[i] != NULL)
	        total_length += ft_strlen(strs[i]);
        i++;
    }
    result = (char *) ft_calloc(total_length + 1, sizeof(char));
    if (!result)
        return (NULL);
    i = 0;
    written = 0;
    while (i < count) {
		if (strs[i] != NULL) {
			total_length = ft_strlen(strs[i]); // not a null ended
			ft_memcpy(result + written, strs[i], total_length);
			written += total_length;
		}
        i++;
    }
    free_join_array(strs, count);
    return (result);
}

//bool is_delimeter(char c);
//static char *handle_dollar_sign_special(char *str, size_t start, t_env_list *list)
//{
//	size_t  i;
//	size_t  length;
//	char *varname;
//
//	(void)list;
//	i = start + 1;
//	while (str[i] != '\0' && is_delimeter(str[i]) == false)
//		i++;
//	length = i - start - 1;
//	varname = ft_substr(str, start + 1, length);
//	// printf("%s\n", varname);
////	*start += length + 1;
//	return (get_env_value(list, varname));
//}

bool is_var_name(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_')
		return (true);
	return (false);
}

static char *handle_last(t_env_list *list, char *str)
{
	size_t	i;
	size_t	size;
	char *key;
	char *value;
	char *result;

	i = 0;
	size = ft_strlen(str);
	while (str[i] && is_var_name(str[i]))
		i++;
	value = ft_substr(str, 0, i);
	key = get_env_value(list, value);
	free(value);
	value = ft_substr(str, i, size - i);
	result = ft_strjoin(key, value);
	if (!value)
		free(value);
	if (!result)
		free(key);
	return (result);
}

char *u(char *str, t_env_list *list) {
	char **splitted;
	bool prefix;
	char **to_join;
	size_t index;
	size_t i;

	to_join = (char **) ft_calloc(100, sizeof(char *));
	index = 0;
	i = 0;
	prefix = true;
	if (*str == '$')
		prefix = false;
	splitted = ft_split(str, '$');
	if (*splitted == NULL)
	{
		free(to_join);
		return (NULL);
	}
	if (prefix)
		to_join[index++] = ft_strdup(splitted[i++]);
	while (splitted[i])
	{
		if (splitted[i + 1] == NULL)
			to_join[index++] = handle_last(list, splitted[i]);
		else
			to_join[index++] = ft_strdup(get_env_value(list, splitted[i]));
		i++;
	}
	return (join(to_join, index));
}

char    *handle_double_quotes(char *str, size_t *start, t_env_list *list)
{
	size_t i;
	char *curr_str;
	char *tmp;
	char *expanded;
	char *result;

	i = *start;
	result = NULL;
	while (str[i]) {
		i = *start + 1;
		while (str[i] && str[i] != '"')
			i++;
		// ""
		curr_str = ft_substr(str, *start + 1, i - *start - 1);
		expanded = u(curr_str, list);
		if (tmp)
		{
			if (result == NULL)
				tmp = ft_strjoin("", expanded);
			else
				tmp = ft_strjoin(result, expanded);
			free(result);
			free(expanded);
			result = tmp;
		}
//		printf("%s\n%s\n", curr_str, tmp);
		free(curr_str);
		*start = i + 2;
		*start = i + 2;
		if (str[i + 1] == '\0')
			break ;
	}
	return (result);
}