
#include "../../includes/expander.h"

// echo "$PATH || $PATH"

char *handle_dollar_sign(char *str, size_t *start, t_env_list *list);

static bool is_space(char c)
{
    // check for expansion delimeters
    return (c == ' ');
}

static void free_join_array(char **strs, size_t count)
{
    size_t i;

    i = 0;
    while (i < count)
    {
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
    while (strs[i] != NULL)
    {
        total_length = ft_strlen(strs[i]);
        ft_memcpy(result + written, strs[i], total_length);
        written += total_length;
        i++;
    }
    free_join_array(strs, count);
    return (result);
}

char    *handle_double_quotes(char *str, size_t *start, t_env_list *list)
{
    size_t i;
    size_t j;
    size_t curr;
    char *to_join[100];
    char *expanded_var;

    i = *start + 1;
    curr = 0;
    while (str[i] != '\0' && str[i] != '"')
    {
        if (str[i] == '$')
        {
            // check if alloc null string
            expanded_var = handle_dollar_sign(&(str[i]), 0, list);
            if (expanded_var)
                to_join[curr++] = expanded_var;
            while (str[i] && !is_space(str[i]))
                i++;
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