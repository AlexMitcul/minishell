


#include "../../includes/expander.h"

void free_strs(char **strs)
{
    size_t i;

    if (!strs)
        return ;
    i = 0;
    while (strs[i])
    {
        free(strs[i]);
        i++;
    }
    free(strs);
}

bool is_var_name(char c)
{
    if ((c >= 'A' && c <= 'Z')
        || (c >= 'a' && c <= 'z')
        || (c >= '0' && c <= '9')
        || (c == '_'))
        return (true);
    return (false);
}

// ! Need to test this function
char *expand_dollar_sign(char *str, size_t start, t_env_list *list)
{
    size_t end;
    char *key;
    char *result;

    end = start + 1;
    if (str[end] && str[end] == '?')
        return (ft_itoa(42)); // Put here status code
    while (str[end] && is_var_name(str[end]))
        end++;
    /*
     *    $PATH
     * 012345678
    */
    key = ft_substr(str, start + 1, end - start + 1);
    result = get_env_value(list, key);
    free(key);
    return (result);
}

// ! Need to test this function
char *expand_single_quotes(char *str, size_t start)
{
    size_t end;
    size_t i;
    char *result;

    end = start + 1;
    while (str[end] && str[end] != '\'')
        end++;
    // start 2 end 6
    result = (char *) ft_calloc(end - start, sizeof(char));
    if (!result)
        return (NULL);
    start++;
    i = 0;
    while (str[start] && start < end)
        result[i++] = str[start++];
    return (result);
}

char *expand_string(char *str)
{
    char *result = NULL;
    (void) str;
//    size_t start;
//    size_t end;

    return (result);
}

char **expand_all_strings(char **strs)
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
        result[index++] = expand_string(strs[curr_string++]);
    return (result);
}

void expand(t_command *cmd)
{
    size_t i;
    char **expanded;

    if (!cmd->str)
        return ;
    i = 0;
    expanded = NULL;
    while (cmd->str[i])
    {
        expanded = expand_all_strings(cmd->str);
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
    (void)app;
//    t_command *cmd;
//
//    cmd = app->commands_list;
//    if (!cmd)
//        return (EXIT_SUCCESS);
//    while (cmd)
//    {
//        expand(cmd);
//        cmd = cmd->next;
//    }

    return (EXIT_SUCCESS);
}