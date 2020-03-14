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

/*----------------------------includes----------------------------*/
# include <unistd.h>
# include <stdlib.h>
# include "cetushell.h"
/*----------------------------defines----------------------------*/
# define PROMPT_LEN 10
# define PROMT_STR "Cetush >>"
# define CLEAR_TO_END "ce"
# define CURSOR_DOWN "do"
# define CLEAR_SCREEN "cl"
# define CURSOR_POSITION "u7"
# define BACKSPACE 127
# define ESCAPE 27
# define RETURN	10
# define TAB 9
# define CNTRL_C 3
/*----------------------------structs----------------------------*/

typedef struct      s_shell t_shell;

typedef struct		s_buff
{
	char			buff[2048];
	size_t			len;
	size_t			index;
}					t_buff;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_cursor
{
	t_point			start;
	t_point			current;
	t_point			max;
	char			cur_buff[32];
}					t_cursor;

/*----------------------------prototypes----------------------------*/

void		send_terminal(char *command);
void		get_winsize(t_shell *shell);
void		configure_terminal(t_shell *shell, int activator);
int			read_input(t_shell *shell);
void		init_buffs(t_shell *shell);
void		insert_char(t_buff *buffer, char c);
void		remove_char(t_buff *buffer);
void		handle_esc_seq(char c, t_cursor *cursor, t_buff *buffer);
void		handle_tab(char c, t_buff *buffer, t_cursor *cursor);
void		get_cursor_pos(t_cursor *cursor, int init);
void		cursor_pos(t_cursor *cursor, int len);
int			prompt_shell(t_shell *shell);

#endif
