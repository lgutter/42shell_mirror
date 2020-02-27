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
<<<<<<< HEAD
=======
# define ESCAPE 27
>>>>>>> 94f42877c650e6d3b196e6ba0808effffb5ce1e8
# define RETURN	10
# define TAB 9
# define CNTRL_C 3

void		handle_backspace(char c, t_buff *buffer, t_cursor *cursor);
void		handle_tab(char c, t_buff *buffer, t_cursor *cursor);
<<<<<<< HEAD
=======
void		handle_esc_seq(char c, t_cursor *cursor);
int			insert_char(t_buff *buffer, t_cursor *cursor, char c);
>>>>>>> 94f42877c650e6d3b196e6ba0808effffb5ce1e8

#endif
