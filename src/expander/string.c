#include "../../libft/includes/libft.h"

typedef struct s_string
{
	char *str;
	size_t	size;
	size_t	capacity;
} t_string;

t_string *string(size_t size)
{
	t_string *string;
	size_t	capacity;

	string = (t_string *) malloc(sizeof(t_string));
	if (!string)
		return (NULL);
	string->capacity = size * 2;
	string->size = 0;
	string->str = ft_calloc(string->capacity + 1, sizeof(char));
	if (!string->str)
	{
		free(string);
		return (NULL);
	}
	return (string);
}

void free_string(t_string *str)
{
	if (!str)
		return ;
	if (!str->str)
	{
		free(str);
		return ;
	}
	free(str->str);
	free(str);
}

t_string *realloc_string(t_string *str)
{
	size_t size;
	t_string *new_string;

	if (!str)
		return (NULL);
	size = str->capacity * 2;
	new_string = string(size);
	ft_memcpy(new_string->str, str->str, str->size);
	new_string->size = str->size;
	free_string(str);
	return (new_string);
}

t_string *cstring(char *str)
{
	t_string *new_string;
	size_t size;

	if (!str)
		return (NULL);
	size = ft_strlen(str);
	new_string = string(size);
	if (!new_string)
		return (NULL);
	new_string->size = size;
	ft_memcpy(new_string->str, str, size);
	return (new_string);
}

t_string *string_append_char(t_string *str, char ch)
{
	if (!str)
		return (NULL);
	if (str->size == str->capacity)
		str = realloc_string(str);
	str->str[str->size] = ch;
	str->size++;
	return (str);
}

