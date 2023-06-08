#ifndef EXPANDER_H
#define EXPANDER_H

# include "minishell.h"
size_t	sign(char *str);
size_t	handle_after_sign(size_t start, char *str);
size_t	question_mark(char **tmp);
size_t	equal_sign(char *str);
size_t	after_dol_length(char *str, size_t start);
char	**expander(t_app *app, char **str);
int	handle_pipe_errors(t_app *app, t_token_type token_type);

#endif
