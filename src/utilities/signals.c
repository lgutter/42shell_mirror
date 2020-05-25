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
