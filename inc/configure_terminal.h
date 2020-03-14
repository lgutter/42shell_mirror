/* ************************************************************************** */
/*                                                                            */
/*   cetushell - 21 Shell                                 ::::::::            */
/*                                                      :+:    :+:            */
/*   By: dkroeke <dkroeke@student.codam.nl>            +:+                    */
/*       lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*                                                 #+#    #+#                 */
/*   License: GPLv3                                ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURE_TERMINAL_H
# define CONFIGURE_TERMINAL_H
# define CURSOR_POSITION "u7"
# define CLEAR_TO_BEGIN "cb"
# define CURSOR_LEFT "le"
# define CURSOR_RIGHT "nd"
# define CURSOR_UP "up"
# define CURSOR_DOWN "do"
# define CLEAR_SCREEN "cl"

# include "cetushell.h"

void		send_terminal(char *command);
void		move_cursor_left(char c, t_cursor *cursor);
void		cursor_pos(t_cursor *cursor, int len);

#endif
