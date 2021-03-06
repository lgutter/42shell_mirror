/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_handling.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:35:25 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/05/10 00:40:34 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_HANDLING_H
# define INPUT_HANDLING_H

/*
**--------------------------Includes------------------------------------------
*/
# include <unistd.h>
# include <stdlib.h>
# include "cetushell.h"
# include "history.h"

/*
**--------------------------Defines-------------------------------------------
*/

# define ESC_SEQ_SIZE   16
# define ARROW_UP       "[A"
# define ARROW_DOWN     "[B"
# define ARROW_RIGHT    "[C"
# define ARROW_LEFT     "[D"
# define END_KEY        "[F"
# define HOME_KEY       "[H"
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
# define CNTRL_S 023
# define CNTRL_V 026
# define CNTRL_X 030

# define TAB_KEY	011
# define RETURN_KEY	012
# define ESCAPE_KEY 033
# define BACKSPACE 0177

/*
**----------------------------Prototypes--------------------------------------
*/

/*
** read_input will take in a pointer to struct t_shell defined in "cetushell".
** it will read the input of the user and process it. The function will return
** an int specifying termination or succesion depending on which key is pressed.
**
** arg: *shell: pointer to struct defined in cetushell.h.
** return: int: succes (0) or error_code
*/
int			read_input(t_shell *shell);

/*
**	frees the allocated read_buff used to buffer extra input.
*/
void		free_read_buff(t_buff *buffer);

/*
**	called right before returning in read_input. It checks if there is more
**	input waiting to be read and expands the read_buff with this input.
*/
void		update_read_buff(t_shell *shell);

/*
** insert_char requires a pointer to the struct t_buff defined in cetushell.h
** and a character which needs to be inserted. The struct has the current index
** and will insert the character in the middle of a string or at the end.
**
** arg: *buffer: pointer to t_buff struct defined in cetushell.h
** arg: char c: the character to be inserted within the buffer(buffer->buff)
*/
int			insert_char(t_buff *buffer, char c);

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

/*
** the tab_key requires as input a pointer to a t_buff and t_cursor struct and
** a character c. This function will insert four spaces and moves the cursor
** accordingly. currently using four actual ' '.
**
** arg: *cursor: pointer to struct t_cursor defined in cetushell.h
** arg: *buffer: pointer to struct t_buff defined in cetushell.h
** arg: c: character input from user which must be TAB_KEY (\011)
*/
void		tab_key(t_shell *shell, char c);

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
** arg: c: character input from user which must be RETURN_KEY (\012)
** return: int: this int must signal the terminal to process the buffer.
*/
int			return_key(t_buff *buffer, char c);

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
int			cut_copy_paste(t_buff *buffer, t_cursor *cursor, char c);

void		remove_word(t_buff *buffer, t_cursor *cursor);

int			ctrl_d_key(char c, t_shell *shell);

void		handle_cntrl_arrows(t_buff *buffer, t_cursor *cursor, char *seq);
#endif
