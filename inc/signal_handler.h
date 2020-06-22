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

# include <signal.h>
# include <stdlib.h>
# include "ft_printf.h"

# define SIGINT_BUFF 1
# define SIG_WINDOW 2

volatile unsigned long g_signal_handler;
void	simple_sigaction(int sig, void handler(int), struct sigaction *old_act);
void	signal_handler_buff(int sig);
void	terminal_signal(int sig);
void	catch_terminal_signal(void);

#endif
