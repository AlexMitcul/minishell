#include "../../includes/expander.h"

size_t expand_single_quotes(char *str, size_t start, char **line)
{
	size_t end;
	size_t i;
	char *result;

	end = start + 1;
	while (str[end] && str[end] != '\'')
		end++;
	result = (char *) ft_calloc(end - start, sizeof(char));
	start++;
	i = 0;
	while (str[start] && start < end)
		result[i++] = str[start++];
	*line = result;
	if (str[end] == '\0')
		return (end);
	return (end + 1);
}
