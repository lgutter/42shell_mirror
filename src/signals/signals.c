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

#include "cetushell.h"
#include "input_control.h"
#include <signal.h>
#include "signal_handler.h"

void	signal_handler_buff(int sig)
{
	if (sig == SIGINT)
		g_signal_handler |= SIGINT_BUFF;
	if (sig == SIGWINCH)
		g_signal_handler |= SIG_WINDOW;
}

void	signal_handler_exec(int sig)
{
	if (sig == SIGINT)
		g_signal_handler |= SIGINT_EXEC;
}

char	*sigint_buffer(char *input)
{
	free(input);
	input = ft_strdup("");
	return (input);
}
