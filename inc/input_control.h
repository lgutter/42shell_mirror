/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_control.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:35:25 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/02/10 16:45:21 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_CONTROL_H
# define INPUT_CONTROL_H

/*
**--------------------------Includes------------------------------------------
*/
# include <unistd.h>
# include <stdlib.h>
# include "cetushell.h"
# include "utils.h"

/*
**--------------------------Defines-------------------------------------------
*/

# define PROMPT_NORMAL "Cetush >>"
# define PROMPT_QUOTE "quote>"
# define PROMPT_DQUOTE "dquote>"
# define PROMPT_PIPE "pipe>"
# define PROMPT_HEREDOC "heredoc>"
# define CLEAR_TO_END "ce"
# define CURSOR_DOWN "do"
# define CLEAR_SCREEN "cl"
# define CURSOR_POSITION "u7"

# define ESC_SEQ_SIZE   16
# define ARROW_UP       "[A"
# define ARROW_DOWN     "[B"
# define ARROW_RIGHT    "[C"
# define ARROW_LEFT     "[D"
# define END            "[F"
# define HOME           "[H"
# define SHIFT_UP       "[1;2A"
# define SHIFT_DOWN     "[1;2B"
# define SHIFT_RIGHT    "[1;2C"
# define SHIFT_LEFT     "[1;2D"
# define CNTRL_UP       "[1;5A"
# define CNTRL_DOWN     "[1;5B"
# define CNTRL_RIGHT    "[1;5C"
# define CNTRL_LEFT     "[1;5D"
# define RV_MODE        "\033[7m"
# define RV_RESET       "\033[m"

# define CNTRL_A 001
# define CNTRL_B 002
# define CNTRL_C 003
# define CNTRL_D 004
# define CNTRL_E 005
# define CNTRL_F 006
# define CNTRL_G 007
# define CNTRL_R 022
# define CNTRL_S 023
# define CNTRL_V 026
# define CNTRL_X 030

# define TAB 011
# define RETURN	012
# define ESCAPE 033
# define BACKSPACE 0177

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
void		get_winsize(t_shell *shell);

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
** read_input will take in a pointer to struct t_shell defined in "cetushell".
** it will read the input of the user and process it. The function will return
** an int specifying termination or succesion depending on which key is pressed.
**
** arg: *shell: pointer to struct defined in cetushell.h.
** return: int: succes (0) or error_code
*/
int			read_input(t_shell *shell);

void	free_buffer_buffs(t_shell *shell, size_t with_copy);

/*
** insert_char requires a pointer to the struct t_buff defined in cetushell.h
** and a character which needs to be inserted. The struct has the current index
** and will insert the character in the middle of a string or at the end.
**
** arg: *buffer: pointer to t_buff struct defined in cetushell.h
** arg: char c: the character to be inserted within the buffer(buffer->buff)
*/
int			insert_char(t_buff *buffer, char c);

size_t		insert_word(t_buff *buffer, t_cursor *cursor, char *word,
						size_t len);

int			up_arrow_key(t_buff *buffer, t_cursor *cursor, t_history *hist,
						char *seq);

int			down_arrow_key(t_buff *buffer, t_cursor *cursor, t_history *hist,
						char *seq);
/*
** remove_char requires a pointer to the struct t_buff defined in cetushell.h.
** The struct has the current index and will remove the character in the middle
** of a string or at the end depending on the index.
**
** arg: *buffer: pointer to t_buff struct defined in cetushell.h
** return: int: succes (0) or error_code
*/
void		remove_char(t_buff *buffer);

/*
** Buff relloc requires a string, the current allocated size and the
** current string length. This function will take a string and will allocate
** a new string with an increased allocated size by the define REALLOC_SIZE.
** it will copy the content from buffer to the new string and returns the new
** string.
** arg: *buffer: An allocated string which requires an increase in size.
** arg: buff_size: The size of the current allocation of buffer.
** arg: len: The actual length (characters) of the buffer
*/

size_t		scroll_hist(t_history *hist, t_buff *buffer,
						t_cursor *cursor, char dir);

size_t		scroll_hist(t_history *hist, t_buff *buffer, t_cursor *cursor,
			char dir);

void	remove_buff(t_buff *buffer, t_cursor *cursor);

/*
** the tab_key requires as input a pointer to a t_buff and t_cursor struct and
** a character c. This function will insert four spaces and moves the cursor
** accordingly. currently using four actual ' '.
**
** arg: *cursor: pointer to struct t_cursor defined in cetushell.h
** arg: *buffer: pointer to struct t_buff defined in cetushell.h
** arg: c: character input from user which must be TAB (\011)
*/
void		tab_key(t_buff *buffer, t_cursor *cursor, char c);

/*
** the backspace_key requires as input a pointer to a t_buff and t_cursor struct
** and a character c. This function will remove a character and will invoke the
** function remove_char().
**
** arg: *buffer: pointer to struct t_buff defined in cetushell.h
** arg: *cursor: pointer to struct t_cursor defined in cetushell.h
** arg: c: character input from user which must be BACKSPACE (\177)
*/
void		backspace_key(t_buff *buffer, t_cursor *cursor, char c);

/*
** the backspace_key requires as input a pointer to a t_buff and t_cursor struct
** and a character c. this function will enter the buffer as input for the rest
** of the terminal process. The function itself will return an int.
**
** arg: *buffer: pointer to struct t_buff defined in cetushell.h
** arg: *cursor: pointer to struct t_cursor defined in cetushell.h
** arg: c: character input from user which must be RETURN (\012)
** return: int: this int must signal the terminal to process the buffer.
*/
int			return_key(t_buff *buffer, t_cursor *cursor, char c);

/*
** the return_key requires as input a pointer to a t_buff and t_cursor struct
** and a string seq. will move the cursor and buffer index to the start of the
** buffer.
**
** arg: *buffer: pointer to struct t_buff defined in cetushell.h
** arg: *cursor: pointer to struct t_cursor defined in cetushell.h
** arg: *seq: The character sequence that is assigned to this control.
*/
void		home_key(t_buff *buffer, t_cursor *cursor, char *seq);

/*
** the return_key requires as input a pointer to a t_buff and t_cursor struct
** and a string seq. will move the cursor and buffer index to the start of the
** buffer.
**
** arg: *buffer: pointer to struct t_buff defined in cetushell.h
** arg: *cursor: pointer to struct t_cursor defined in cetushell.h
** arg: *seq: The character sequence that is assigned to this control.
*/
void		end_key(t_buff *buffer, t_cursor *cursor, char *seq);

/*
** the left_arrow_key requires as input a pointer to a t_buff and t_cursor
** struct and a string seq.This function will move the cursor one step left.
**
** arg: *buffer: pointer to struct t_buff defined in cetushell.h
** arg: *cursor: pointer to struct t_cursor defined in cetushell.h
** arg: *seq: The character sequence that is assigned to this control.
*/
void		left_arrow_key(t_buff *buffer, t_cursor *cursor, char *seq);

/*
** the right_arrow_key requires as input a pointer to a t_buff and t_cursor
** struct and a string seq.This function will move the cursor one step right.
**
** arg: *buffer: pointer to struct t_buff defined in cetushell.h
** arg: *cursor: pointer to struct t_cursor defined in cetushell.h
** arg: *seq: The character sequence that is assigned to this control.
*/
void		right_arrow_key(t_buff *buffer, t_cursor *cursor, char *seq);

/*
** the shift_left_arrow_key requires as input a pointer to a t_buff and t_cursor
** struct and a string seq.This function will move the cursor one step left and
** will keep the previous character highlighted.
**
** arg: *buffer: pointer to struct t_buff defined in cetushell.h
** arg: *cursor: pointer to struct t_cursor defined in cetushell.h
** arg: *seq: The character sequence that is assigned to this control.
*/
void		shift_left_key(t_buff *buffer, t_cursor *cursor, char *seq);

/*
** the shift_left_arrow_key requires as input a pointer to a t_buff and t_cursor
** struct and a string seq.This function will move the cursor one step right and
** will keep the previous character highlighted.
**
** arg: *buffer: pointer to struct t_buff defined in cetushell.h
** arg: *cursor: pointer to struct t_cursor defined in cetushell.h
** arg: *seq: The character sequence that is assigned to this control.
*/
void		shift_right_key(t_buff *buffer, t_cursor *cursor, char *seq);

/*
** cut_copy_paste requires as input a pointer to a t_buff struct and t_cursor
** struct. It also requires either a string seq or character c which will define
** what control character is pressed on the keyboard. This function will copy
** text from buffer, cut text from the buffer and copies it or paste the copied
** text into the buffer depending on the pressed key combination.
**
** arg: *buffer: pointer to struct t_buff defined in cetushell.h
** arg: *cursor: pointer to struct t_cursor defined in cetushell.h
** arg: *seq: The character sequence that is assigned to this control.
** arg: c: a character which defines what control is used.
** return:
*/
int			cut_copy_paste(t_buff *buffer, t_cursor *cursor, char *seq, char c);

void		remove_word(t_buff *buffer, t_cursor *cursor);

/*
** set_cursor_pos will set the current cursor position defined in the t_cursor
** struct (x,y) and uses the buffer len as limitation. It translates the
** coordinates to a string (cur_buff) which then can be used to send an
** instruction to the terminal.
**
** arg: *cursor: pointer to t_cursor struct defined in cetushell.h.
** arg: len: the buffer max len to prevent the cursor from going over it.
*/
void		set_cursor_pos(t_cursor *cursor, size_t buff_len,
	size_t prompt_len);

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

#endif
