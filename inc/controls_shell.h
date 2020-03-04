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

#ifndef CONTROLS_SHELL_H
# define CONTROLS_SHELL_H

# define BACKSPACE 127
# define ESCAPE 27
# define RETURN	10
# define TAB 9
# define CNTRL_C 3

void		handle_backspace(char c, t_buff *buffer, t_cursor *cursor);
void		handle_tab(char c, t_buff *buffer, t_cursor *cursor);
void		handle_esc_seq(char c, t_cursor *cursor, t_buff *buffer);
void		insert_char(t_buff *buffer, char c);

#endif
