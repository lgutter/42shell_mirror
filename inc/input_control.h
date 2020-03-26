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


/*----------------------------Prototypes--------------------------------------*/

/**
 * send_terminal will require a command specified by (5) terminfo under 
 * termcap codes. This will send a instruction to the terminal by looking at 
 * which terminal is running. This can make it usefull to make sure that this 
 * program works on every terminal.
 * 
 * arg: command: string command specified in man (5) terminfo.
 */
void		send_terminal(char *command);

/**
 * get_winsize will require a pointer struct t_shell specified in "cetushell.h".
 * It will get the current window size and sets this into a winsize struct. This
 * is needed to print the prompt,input and output correctly.
 * 
 * arg: *shell: poiter to struct t_shell defined in cethushell.h
 */
void		get_winsize(t_shell *shell);

/**
 * Configure_terminal will take in a pointer to a t_shell struct defined in
 * "cetushell.h" and a activator. It wil then put the terminal in 
 * RAW mode (activator = 1), or put the original terminal settings back 
 * (avtivator = 0). The original terminal will be saved in a static within the 
 * function. This function is needed to be able to control the process input
 * handling of the terminal.
 * 
 * arg:    *shell: pointer to struct defined in cetushell.h.
 * arg: activator; 1 for activation of RAW mode, 0 for returning original 
 *                 settings.
 */
void		configure_terminal(t_shell *shell, int activator);

/**
 * read_input will take in a pointer to struct t_shell defined in "cetushell".
 * it will read the input of the user and process it. The function will return
 * an int specifying termination or succesion depending on which key is pressed.
 * 
 * arg: *shell: pointer to struct defined in cetushell.h.
 */
int			read_input(t_shell *shell);

/**
 * init_buffs will initialize all the buffers needed for input of the shell. It
 * requires s pointer to the struct t_shell defined in cethushell.h.
 * 
 * arg: *shell: pointer to struct defined in cetushell.h.
 */
void		init_buffs(t_shell *shell);

/**
 * insert_char requires a pointer to the struct t_buff defined in cetushell.h
 * and a character which needs to be inserted. The struct has the current index
 * and will insert the character in the middle of a string or at the end.
 * 
 * arg: *buffer: pointer to t_buff struct defined in cetushell.h
 * arg: char c: the character to be inserted within the buffer(buffer->buff)
 */
void		insert_char(t_buff *buffer, char c);

/**
 * remove_char requires a pointer to the struct t_buff defined in cetushell.h. 
 * The struct has the current index and will remove the character in the middle
 * of a string or at the end depending on the index.
 * 
 * arg: *buffer: pointer to t_buff struct defined in cetushell.h
 */
void		remove_char(t_buff *buffer);

/**
 * read_esc_seq requires as input a char, a pointer to the t_cursor and t_buff
 * struct. When the first character is an escape character, this function will
 * read out the additional sequence characters. this is required for some keys
 * to work in RAW mode of the terminal.
 * 
 * arg: c: character input from user which must be ESCAPE (\033)
 * arg: *cursor: pointer to struct t_cursor defined in cetushell.h
 * arg: *buffer: pointer to struct t_buff defined in cetushell.h
 */
void		read_esc_seq(char c, t_cursor *cursor, t_buff *buffer);

/**
 * the tab_key requires as input a pointer to a t_buff and t_cursor struct and
 * a character c. This function will insert four spaces and moves the cursor 
 * accordingly. currently using four actual ' '.
 * 
 * arg: *cursor: pointer to struct t_cursor defined in cetushell.h
 * arg: *buffer: pointer to struct t_buff defined in cetushell.h
 * arg: c: character input from user which must be TAB (\011)
 */
void		tab_key(t_buff *buffer, t_cursor *cursor, char c);

/**
 * the backspace_key requires as input a pointer to a t_buff and t_cursor struct
 * and a character c. This function will remove a character and will invoke the
 * function remove_char().
 * 
 * arg: *cursor: pointer to struct t_cursor defined in cetushell.h
 * arg: *buffer: pointer to struct t_buff defined in cetushell.h
 * arg: c: character input from user which must be BACKSPACE (\177)
 */
void		backspace_key(t_buff *buffer, t_cursor *cursor, char c);

/**
 * the backspace_key requires as input a pointer to a t_buff and t_cursor struct
 * and a character c. this function will enter the buffer as input for the rest
 * of the terminal process. The function itself will return an int.
 * 
 * arg: *cursor: pointer to struct t_cursor defined in cetushell.h
 * arg: *buffer: pointer to struct t_buff defined in cetushell.h
 * arg: c: character input from user which must be RETURN (\012)
 * return: int: this int must signal the terminal to process the buffer.
 */
int			return_key(t_buff *buffer, t_cursor *cursor, char c);

void		home_key(t_buff *buffer, t_cursor *cursor, char *seq);

void		end_key(t_buff *buffer, t_cursor *cursor, char *seq);

void		left_arrow_key(t_buff *buffer, t_cursor *cursor, char *seq);

void		right_arrow_key(t_buff *buffer, t_cursor *cursor, char *seq);

void		shift_left_key(t_buff *buffer, t_cursor *cursor, char *seq);

void        shift_right_key(t_buff *buffer, t_cursor *cursor, char *seq);

<<<<<<< HEAD
void		cut_copy_paste(t_buff *buffer, t_cursor *cursor, char *seq, char c);
=======
void		cut_cntrl_left(t_buff *buffer, t_cursor *cursor, char *seq);
>>>>>>> 461c721e986a64e022db25670cf2f321f0f72195

/**
 * set_cursor_pos will set the current cursor position defined in the t_cursor
 * struct (x,y) and uses the buffer len as limitation. It translates the 
 * coordinates to a string (cur_buff) which then can be used to send an 
 * instruction to the terminal.
 * 
 * arg: *cursor: pointer to t_cursor struct defined in cetushell.h.
 * arg: len: the buffer max len to prevent the cursor from going over it.
 */
void		set_cursor_pos(t_cursor *cursor, size_t len);

/**
 * get_cursor_pos will get the starting cursor position and will set its 
 * coordinates accordingly into the t_cursor struct.
 * 
 * arg: *cursor: pointer to t_cursor struct defined in cetushell.h
 */
void		get_cursor_pos(t_cursor *cursor);

/**
 * prompt_shell will require the t_shell struct as input and will show  and 
 * refresh the prompt after every iteration.
 * 
 * arg: *shell: pointer to t_shell struct defined in cetushell.h
 */
int			prompt_shell(t_shell *shell);

#endif
