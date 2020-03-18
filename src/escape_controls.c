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
	if (strncmp(seq, HOME, ft_strlen(HOME)) == 0)
	{
		cursor->current.x = PROMPT_LEN;
		cursor->current.y = cursor->start.y;
		buffer->index = 0;
	}
}

void		end_key(t_buff *buffer, t_cursor *cursor, char *seq)
{
	if (strncmp(seq, END, ft_strlen(END)) == 0)
	{
		cursor->current.x = (buffer->len + PROMPT_LEN) % cursor->max.x;
		cursor->current.y = cursor->current.y + (buffer->len / cursor->max.x);
		buffer->index = buffer->len;
	}
}