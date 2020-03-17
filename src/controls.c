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

void		left_arrow_key(t_buff *buffer, t_cursor *cursor, char *seq)
{
	if (ft_strncmp(seq, ARROW_LEFT, ft_strlen(ARROW_LEFT)) &&
					 cursor->current.x > 0)
		{
			if (buffer->index != 0)
			{
				buffer->index--;
				cursor->current.x--;
			}
		}
}

void		right_arrow_key(t_buff *buffer, t_cursor *cursor, char *seq)
{
	if (ft_strncmp(seq, ARROW_RIGHT, ft_strlen(ARROW_RIGHT)))
	{
		if (buffer->index < buffer->len)
		{
			cursor->current.x++;
			buffer->index++;
		}
	}
}

void		home_key(t_buff *buffer, t_cursor *cursor, char *seq)
{
	ft_printf("\ntest1 = (%s), %d\n", seq, strncmp(seq, HOME, ft_strlen(HOME)));
	if (strncmp(seq, HOME, ft_strlen(HOME)) == 0)
	{
		cursor->current.x = PROMPT_LEN;
		cursor->current.y = cursor->start.y;
		buffer->index = 0;
	}
}

void		end_key(t_buff *buffer, t_cursor *cursor, char *seq)
{
	ft_printf("\ntest1 = (%s), %d\n", seq, strncmp(seq, HOME, ft_strlen(HOME)));
	if (strncmp(seq, END, ft_strlen(END)) == 0)
	{
		cursor->current.x = (buffer->len + PROMPT_LEN) % cursor->max.x;
		cursor->current.y = cursor->current.y + (buffer->len / cursor->max.x);
		buffer->index = buffer->len;
	}
}