/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   terminal.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/16 16:09:07 by dkroeke        #+#    #+#                */
/*   Updated: 2020/02/16 16:09:07 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H
# define CURSOR_POSITION "u7"
# define CLEAR_TO_BEGIN "cb"
# define CURSOR_LEFT "le"
# define CURSOR_RIGHT "nd"
# define CURSOR_UP "up"
# define CURSOR_DOWN "do"
# define CLEAR_SCREEN "cl"

# include "shell21.h"

void		send_terminal(char *command);

#endif
