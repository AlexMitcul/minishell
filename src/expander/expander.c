


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


char *expand_string(char *str)
{
    char *result;
    size_t start;
    size_t end;

    return (result);
}

char **expand_all_strings(char **strs)
{
    char **result;
    size_t curr_string;
    size_t index;

    if (!strs)
        return (NULL);
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
    t_command *cmd;

    cmd = app->commands_list;
    if (!cmd)
        return (EXIT_SUCCESS);
    while (cmd)
    {
        expand(cmd);
        cmd = cmd->next;
    }

    return (EXIT_SUCCESS);
}