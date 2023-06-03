//
// Created by amitcul on 6/3/23.
//

#ifndef MINISHELL_GLOBAL_H
#define MINISHELL_GLOBAL_H

struct s_global
{
	int error_num;
	int stop_heredoc;
	int in_cmd;
	int in_heredoc;
};

extern struct s_global g_status;

#endif
