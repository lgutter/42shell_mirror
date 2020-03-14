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

#include "cetushell.h"
#include "controls_shell.h"
#include "configure_terminal.h"

/**
 * Handle escape sequence will read the STDIN for escape sequence combinations.
 * For example, arrow keys are escape code /e[A, /e[B etc. Handle escape
 * sequence will get the escape character(27) and then read 2 more characters.
 * the second two characters will be compared. 
 */
void		handle_esc_seq(char c, t_cursor *cursor, t_buff *buffer)
{
	char	seq[3];

	ft_bzero(seq, 3);
	if (c == ESCAPE)
	{
		if (read(STDIN_FILENO, &seq[0], 1) == -1)
			return ;
		if (read(STDIN_FILENO, &seq[1], 1) == -1)
			return ;
		if (seq[0] == 91 && seq[1] == 'D' && cursor->current.x > 0)
		{
			if (buffer->index != 0)
			{
				buffer->index--;
				cursor->current.x--;
			}
		}
		if (seq[0] == 91 && seq[1] == 'C')
		{
			if (buffer->index < buffer->len)
			{
				cursor->current.x++;
				buffer->index++;
			}
		}
	}
}

/**
 * Handle_tab will input 4 spaces into the buffer instead of adding /t. This to
 * keep buffer managment easier to handle. IMPLEMENT: autocomplete when in a
 * word.
 */
void		handle_tab(char c, t_buff *buffer, t_cursor *cursor)
{
	int		i;

	i = 0;
	if (c == TAB)
	{
		while (i != 4)
		{
			cursor->x_max = 0;
			insert_char(buffer, ' ');
			cursor->current.x++;
			i++;
		}
	}
}
