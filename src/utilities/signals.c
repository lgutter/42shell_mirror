/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/18 12:49:02 by devan         #+#    #+#                 */
/*   Updated: 2020/05/23 16:21:37 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"

void	signal_handler_buff(int sig)
{
	if (sig == SIGINT)
		g_signal_handler = SIGINT_BUFF;
	if (sig == SIGWINCH)
		g_signal_handler = SIG_WINDOW;
}

void	terminal_signal(int sig)
{
	ft_printf("a subshell sent signal %i to cetushell, ", sig);
	ft_printf("which means we no longer have access to the terminal!\n");
	ft_printf("We can't fix this issue with the allowed functions in 21sh.\n");
	ft_printf("aborting cetushell, exit.\n");
	exit(1);
}

void	catch_terminal_signal(void)
{
	signal(SIGTTIN, terminal_signal);
	signal(SIGTTOU, terminal_signal);
}
