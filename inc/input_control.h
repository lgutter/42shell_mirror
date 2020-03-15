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

#ifndef INPUT_CONTROL_H
# define INPUT_CONTROL_H

/*--------------------------Includes------------------------------------------*/
# include <unistd.h>
# include <stdlib.h>
# include "cetushell.h"
/*--------------------------Defines-------------------------------------------*/
# define PROMPT_LEN 10
# define PROMPT_STR "Cetush >>"

# define CLEAR_TO_END "ce"
# define CURSOR_DOWN "do"
# define CLEAR_SCREEN "cl"
# define CURSOR_POSITION "u7"

# define ARROW_UP "\e[A"
# define ARROW_DOWN "\e[B"
# define ARROW_RIGHT "\e[C"
# define ARROW_LEFT "\e[D"
# define BACKSPACE 127
# define ESCAPE 27
# define RETURN	10
# define TAB 9
# define CNTRL_C 3
/*--------------------------Structs-------------------------------------------*/



/*----------------------------Prototypes--------------------------------------*/

void		send_terminal(char *command);
void		get_winsize(t_shell *shell);
void		configure_terminal(t_shell *shell, int activator);

int			read_input(t_shell *shell);
void		init_buffs(t_shell *shell);
void		insert_char(t_buff *buffer, char c);
void		remove_char(t_buff *buffer);
void		read_esc_seq(char c, t_cursor *cursor, t_buff *buffer);


void		handle_tab(t_buff *buffer, t_cursor *cursor, char c);
void		handle_backspace(t_buff *buffer, t_cursor *cursor, char c);
void		handle_tab_key(t_buff *buffer, t_cursor *cursor, char c);
void		handle_backspace_key(t_buff *buffer, t_cursor *cursor, char c);
int			handle_return_key(t_buff *buffer, t_cursor *cursor, char c);


void		set_cursor_pos(t_cursor *cursor, int len);
void		get_cursor_pos(t_cursor *cursor);

int			prompt_shell(t_shell *shell);

#endif
