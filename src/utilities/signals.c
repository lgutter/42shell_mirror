/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/18 12:49:02 by devan         #+#    #+#                 */
/*   Updated: 2020/07/08 20:15:40 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"

void	simple_sigaction(int sig, void handler(int), struct sigaction *old_act)
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = handler;
	sigaction(sig, &action, old_act);
}

void	signal_handler(int sig)
{
	if (sig <= 32)
		g_signal_handler |= (1 << sig);
}

void	setup_signals(void)
{
	simple_sigaction(SIGINT, signal_handler, NULL);
	simple_sigaction(SIGWINCH, signal_handler, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}

void	reset_signals(void)
{
	simple_sigaction(SIGINT, SIG_DFL, NULL);
	simple_sigaction(SIGWINCH, SIG_DFL, NULL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
}
