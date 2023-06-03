//
// Created by amitcul on 6/3/23.
//

#ifndef MINISHELL_SIGNAL_HANDLERS_H
#define MINISHELL_SIGNAL_HANDLERS_H

void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	init_signals(void);

#endif //MINISHELL_SIGNAL_HANDLERS_H
