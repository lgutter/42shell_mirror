/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:35:25 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/05/10 00:40:34 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

/*
**--------------------------Includes------------------------------------------
*/
# include <unistd.h>
# include <stdlib.h>
# include "cetushell.h"
# include "utils.h"
# include "history.h"

/*
**--------------------------Defines-------------------------------------------
*/

# define PROMPT_NORMAL_COLOUR "\033[38;5;75mCetush »\033[0;00m "
# define PROMPT_NORMAL "Cetush > "
# define PROMPT_QUOTE "quote> "
# define PROMPT_DQUOTE "dquote> "
# define PROMPT_BACKSLASH "backslash> "
# define PROMPT_HEREDOC "heredoc> "
# define CLEAR_TO_END "ce"
# define TERM_DOWN "do"
# define CLEAR_SCREEN "cl"
# define CURSOR_POSITION "u7"

# define CURSOR_UP		2
# define CURSOR_RIGHT	1
# define CURSOR_LEFT	-1
# define CURSOR_DOWN	-2
# define RM_NEWLINE		4
# define RM_LEFT		5
# define ESCAPE_KEY 	033

/*
**----------------------------Prototypes--------------------------------------
*/

/*
** send_terminal will require a command specified by (5) terminfo under
** termcap codes. This will send a instruction to the terminal by looking at
** which terminal is running. This can make it usefull to make sure that this
** program works on every terminal.
**
** arg: command: string command specified in man (5) terminfo.
*/
void		send_terminal(char *command);

/*
** get_winsize will require a pointer struct t_shell specified in "cetushell.h".
** It will get the current window size and sets this into a winsize struct. This
** is needed to print the prompt,input and output correctly.
**
** arg: *shell: poiter to struct t_shell defined in cethushell.h
*/
void		get_winsize(t_cursor *cursor, size_t len);

/*
** Configure_terminal will take in a pointer to a t_shell struct defined in
** "cetushell.h" and a activator. It wil then put the terminal in
** RAW mode (activator = 1), or put the original terminal settings back
** (avtivator = 0). The original terminal will be saved in a static within the
** function. This function is needed to be able to control the process input
** handling of the terminal.
**
** arg:    *shell: pointer to struct defined in cetushell.h.
** arg: activator; 1 for activation of RAW mode, 0 for returning original
**                 settings.
*/
void		configure_terminal(t_shell *shell, int activator);

/*
** set_cursor_pos will set the current cursor position defined in the t_cursor
** struct (x,y) and uses the buffer len as limitation. It translates the
** coordinates to a string (cur_buff) which then can be used to send an
** instruction to the terminal.
**
** arg: *cursor: pointer to t_cursor struct defined in cetushell.h.
** arg: len: the buffer max len to prevent the cursor from going over it.
*/
void		set_cursor_pos(t_cursor *cursor, t_buff *buffer);

/*
** get_cursor_pos will get the starting cursor position and will set its
** coordinates accordingly into the t_cursor struct.
**
** arg: *cursor: pointer to t_cursor struct defined in cetushell.h
*/
void		get_cursor_pos(t_cursor *cursor, size_t prompt_len);

/*
** prompt_shell will require the t_shell struct as input and will show  and
** refresh the prompt after every iteration.
**
** arg: *shell: pointer to t_shell struct defined in cetushell.h
*/
char		*prompt_shell(t_shell *shell, const char *prompt);

void		free_buffer_buffs(t_shell *shell, size_t with_copy);

void		remove_buff(t_buff *buffer, t_cursor *cursor);

size_t		insert_word(t_buff *buffer, t_cursor *cursor, char *word,
							size_t len);

#endif
