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

void		shift_right_key(t_buff *buffer, t_cursor *cursor, char *seq)
{
	if (ft_strncmp(seq, SHIFT_RIGHT, ft_strlen(SHIFT_RIGHT)) == 0)
		{
			if (buffer->index < buffer->len)
			{
				if (buffer->rv_start == buffer->rv_end)
				{
					buffer->rv_end = buffer->index + 1;
					buffer->rv_start = buffer->index;
				}
				else
					buffer->rv_end = buffer->index + 1;
				buffer->index++;
				cursor->current.x++;
			}
		}
}

void		shift_left_key(t_buff *buffer, t_cursor *cursor, char *seq)
{
	if (ft_strncmp(seq, SHIFT_LEFT, ft_strlen(SHIFT_LEFT)) == 0 &&
					 cursor->current.x > 0)
		{
			if (buffer->index != 0)
			{
				if (buffer->rv_start == buffer->rv_end)
				{
					buffer->rv_end = buffer->index;
					buffer->rv_start = buffer->index + 1;
				}
				else
					buffer->rv_end = buffer->index - 1;
				buffer->index--;
				cursor->current.x--;
			}
		}
}

void		left_arrow_key(t_buff *buffer, t_cursor *cursor, char *seq)
{
	if (ft_strncmp(seq, ARROW_LEFT, ft_strlen(ARROW_LEFT)) == 0 &&
					 cursor->current.x > 0)
		{
			buffer->rv_start = buffer->rv_end;
			if (buffer->index != 0)
			{
				buffer->index--;
				cursor->current.x--;
			}
		}
}

void		right_arrow_key(t_buff *buffer, t_cursor *cursor, char *seq)
{
	if (ft_strncmp(seq, ARROW_RIGHT, ft_strlen(ARROW_RIGHT)) == 0)
	{
		buffer->rv_start = buffer->rv_end;
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