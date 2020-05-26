/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   escape_controls_1.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:52:43 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/04/14 11:52:43 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"

void		shift_right_key(t_buff *buffer, t_cursor *cursor, char *seq)
{
	if (ft_strncmp(seq, SHIFT_RIGHT, ft_strlen(SHIFT_RIGHT)) == 0)
	{
		if (buffer->index < buffer->buff_len - 1)
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
		if (buffer->index == buffer->buff_len)
		{
			buffer->index--;
			cursor->current.x--;
		}
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

void		home_key(t_buff *buffer, t_cursor *cursor, char *seq)
{
	if (ft_strncmp(seq, HOME_KEY, ft_strlen(HOME_KEY)) == 0)
	{
		cursor->current.x = buffer->prompt_len;
		cursor->current.y = cursor->start.y;
		buffer->index = 0;
	}
}

void		end_key(t_buff *buffer, t_cursor *cursor, char *seq)
{
	if (ft_strncmp(seq, END_KEY, ft_strlen(END_KEY)) == 0)
	{
		cursor->current.x = (buffer->buff_len + buffer->prompt_len)\
							% cursor->max.x;
		cursor->current.y = cursor->current.y + (buffer->buff_len
		/ cursor->max.x);
		buffer->index = buffer->buff_len;
	}
}
