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
#include "input_control.h"

int			return_key(t_buff *buffer, t_cursor *cursor, char c)
{
	if (c == RETURN)
	{
		ft_printf("\noutput : %s", buffer->buff);
		get_cursor_pos(cursor);
		ft_memset(&buffer->buff, '\0', buffer->len);
		buffer->len = 0;
		buffer->index = 0;
		send_terminal(CURSOR_DOWN);
	}
	return (0);
}

void		tab_key(t_buff *buffer, t_cursor *cursor, char c)
{
	int		i;

	i = 0;
	if (c == TAB)
	{
		while (i != 4)
		{
			insert_char(buffer, ' ');
			cursor->current.x++;
			i++;
		}
	}
}

void		backspace_key(t_buff *buffer, t_cursor *cursor, char c)
{
	if (c == BACKSPACE)
	{
		if (cursor->current.y == cursor->start.y && \
			cursor->current.x > PROMPT_LEN)
		{
			cursor->current.x--;
			remove_char(buffer);
		}
		else if (cursor->current.y != cursor->start.y)
		{
			cursor->current.x--;
			remove_char(buffer);
		}
	}
}
