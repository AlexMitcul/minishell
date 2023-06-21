#include "../../includes/expander.h"

extern int	g_exit_status;

size_t expand_dollar_sign(char *str, size_t start, char **line, t_env_list *list)
{
	size_t end;
	char *key;
	char *result;

	end = start + 1;
	if (str[end] && str[end] == '?')
	{
		*line = ft_itoa(g_exit_status);
		return (start + 2);
	}
	if (str[end] && is_var_name(str[end]) == false)
	{
		result = ft_substr(str, start, 2);
		*line = result;
		return (end + 1);
	}
	while (str[end] && is_var_name(str[end]))
		end++;
	key = ft_substr(str, start + 1, end - start - 1);
	result = get_env_value(list, key);
	if (result)
		result = ft_strdup(result);
	free(key);
	*line = result;
	return (end);
}
