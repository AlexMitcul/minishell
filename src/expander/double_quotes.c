
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
        total_length += ft_strlen(strs[i]);
        i++;
    }
    result = (char *) ft_calloc(total_length + 1, sizeof(char));
    if (!result)
        return (NULL);
    i = 0;
    written = 0;
    while (i < count)
    {
        total_length = ft_strlen(strs[i]); // not a null ended
        ft_memcpy(result + written, strs[i], total_length);
        written += total_length;
        i++;
    }
    free_join_array(strs, count);
    return (result);
}

bool is_delimeter(char c);
static char *handle_dollar_sign_special(char *str, size_t start, t_env_list *list)
{
	size_t  i;
	size_t  length;
	char *varname;

	(void)list;
	i = start + 1;
	while (str[i] != '\0' && is_delimeter(str[i]) == false)
		i++;
	length = i - start - 1;
	varname = ft_substr(str, start + 1, length);
	// printf("%s\n", varname);
//	*start += length + 1;
	return (get_env_value(list, varname));
}

char    *handle_double_quotes(char *str, size_t *start, t_env_list *list)
{
    size_t i;
    size_t j;
    size_t curr;
    char **to_join;
    char *expanded_var;

    i = *start + 1;
    curr = 0;
	to_join = ft_calloc(100, sizeof(char *));
    while (str[i] != '\0' && str[i] != '"')
    {
        if (str[i] == '$')
        {
            // check if alloc null string
            expanded_var = handle_dollar_sign_special(&(str[i]), 0, list);
            if (expanded_var)
                to_join[curr++] = ft_strdup(expanded_var);
			// need to pass name of expanded part. Крч, не скипает слово которые расскрыло,
			// надо цикл бахнуть чтоб скипнул
        }
        else
        {
            j = i;
            while (str[j] && str[j] != '$')
                j++;
            to_join[curr] = ft_calloc(j - i + 1, sizeof(char));
            ft_memcpy(to_join[curr++], &(str[i]), j - i);
            i = j;
        }
    }
    return (join(to_join, curr));
}