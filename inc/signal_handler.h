/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/23 13:38:33 by devan         #+#    #+#                 */
/*   Updated: 2020/05/23 15:37:54 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

#include <signal.h>

# define SIGINT_BUFF    (1 << 1)
# define SIGINT_EXEC    (1 << 2)
# define SIG_WINDOW     (1 << 3)

unsigned long g_signal_handler;


void	signal_handler_buff(int sig);
void	signal_handler_exec(int sig);
char	*sigint_buffer(char *input);

#endif
