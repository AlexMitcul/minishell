#ifndef EXPANDER_H
#define EXPANDER_H

# include "minishell.h"

char	**expander(t_app *app, char **str);
char	*expander_str(t_app *app, char *str);

#endif