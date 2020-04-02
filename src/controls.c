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
		send_terminal(CURSOR_DOWN);
		ft_printf("output : %s\n", buffer->buff);
		get_cursor_pos(cursor);
		ft_memset(&buffer->buff, '\0', buffer->len);
		buffer->len = 0;
		buffer->index = 0;
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
		if (buffer->rv_end != buffer->rv_start)
		{
			ft_swap_rv(buffer);
			remove_word(buffer, cursor);
		}
		else if ((cursor->current.y == cursor->start.y && \
			cursor->current.x > PROMPT_LEN) || cursor->current.y != cursor->start.y)
		{
			cursor->current.x--;
			remove_char(buffer);
		}
	}
}
