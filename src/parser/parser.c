/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amitcul <amitcul@student.42porto.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:19:13 by amitcul           #+#    #+#             */
/*   Updated: 2023/02/18 17:00:34 by amitcul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

#include <stdio.h>

#include <string.h>

//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size])
		size += 1;
	return (size);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < dstsize)
		ft_memcpy(dst, src, srclen + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (srclen);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		length;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (length + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (*s1)
	{
		res[i++] = *s1;
		s1 += 1;
	}
	while (*s2)
	{
		res[i++] = *s2;
		s2 += 1;
	}
	res[i] = '\0';
	return (res);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int				i;
	unsigned char	*d;
	unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (n > 0)
	{
		d[i] = s[i];
		i += 1;
		n -= 1;
	}
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, len + 1);
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	symbol;

	symbol = c;
	while (*s != '\0')
	{
		if (*s == symbol)
			return ((char *)s);
		s++;
	}
	if (*s == '\0' && c == '\0')
		return ((char *)s);
	return (NULL);
}

//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------

#define S_SYMBOLS " <>;|'\""

typedef enum e_token_type
{
	TEXT,
	COMMAND,
	SPECIAL_SYMBOL,
	NO_TYPE
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = NO_TYPE;
	token->value = NULL;
	return (token);
}

void	free_dll(t_dll_item *list)
{
	t_dll_item	*curr;

	if (!list)
		return ;
	curr = list->next;
	while (curr)
	{
		free(curr->prev);
		curr = curr->next;
	}
	free(curr->prev);
}

void	free_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->value != NULL)
		free(token->value);
	free(token);
}

void	string_join(char **str, char *to_add)
{
	char	*new_str;

	if (to_add == NULL)
		return ;
	if (*str == NULL)
	{
		*str = to_add;
		return ;
	}
	new_str = ft_strjoin(*str, to_add);
	free(*str);
	free(to_add);
	*str = new_str;
}

t_token	*parse_started_from_spec_symbol(char *input, int *i, int *j)
{
	t_token	*token;

	if (input[*j] == '\'' || input[*j] == '\"')
		token = parse_quotes(input, i, j);
	else if (input[*j] == '<' || input[*j] == '>')
		token = parse_redirects(input, i, j);
	return (token);
}

int	parse_plain_text(t_token *token, char *input, int i, int *j)
{
	return (EXIT_SUCCESS);
}

t_token	*get_next_token(char **input)
{
	t_token	*token;
	int		i;
	int		j;
	int		status;

	token = init_token();
	if (!token)
		return (NULL);
	i = 0;
	while (input[i] != '\0')
	{
		j = i + 1;
		if (ft_strchr(S_SYMBOLS, input[j]) == NULL)
			status = parse_plain_text(token, input, i, &j);
		else
			status = parse_started_from_spec_symbol(input, &i, &j);
		if (status == EXIT_FAILURE)
			return (free_token(token), NULL);
		i = j;
	}
	return (token);
}

int	parser(t_dll_item *token_list, char *input)
{
	t_dll_item	*list;
	t_token		*token;
	char		*tmp_input;

	list = NULL;
	token = get_next_token(&tmp_input);
	while (token != NULL)
	{
		dll_append(&list, (void *)token);
		get_next_token(&input);
	}
	token_list = list;
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_dll_item	*token_list;

	token_list = NULL;
	if (argc > 1)
	{
		parser(argv[1], token_list);
	}
	return (0);
}
