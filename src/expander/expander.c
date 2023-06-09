

#include "../../includes/expander.h"



int expander(t_app *app)
{
	t_command *command;
	char **expanded;

	command = app->commands_list;
	while (command)
	{
		expanded = expand(app->env_list, command->str);
	}
}
