
#include "../../includes/expander.h"

char	*handle_single_quotes(char *str, size_t *start)
{
    size_t i;
    size_t len;
    char *result;

    i = *start + 1;
    while (str[i] != '\0' && str[i] != '\'')
        i++;
    len = i - *start - 1;
    result = (char *)ft_calloc(len + 1, sizeof(char));
    ft_memcpy(result, str + *start + 1, len);
    *start += len + 2;
    return (result);
}