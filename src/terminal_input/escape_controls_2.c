/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   escape_controls_2.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:52:43 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/04/14 11:52:43 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "prompt.h"
#include "input_handling.h"

void			left_arrow_key(t_buff *buffer, t_cursor *cursor, char *seq)
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
		cursor->direction = CURSOR_LEFT;
	}
}

void			right_arrow_key(t_buff *buffer, t_cursor *cursor, char *seq)
{
	if (ft_strncmp(seq, ARROW_RIGHT, ft_strlen(ARROW_RIGHT)) == 0)
	{
		buffer->rv_start = buffer->rv_end;
		if (buffer->index < buffer->buff_len)
		{
			cursor->current.x++;
			buffer->index++;
			cursor->direction = CURSOR_RIGHT;
		}
	}
}

int				up_arrow_key(t_buff *buffer, t_cursor *cursor, t_history *hist,
						char *seq)
{
	if (ft_strncmp(seq, ARROW_UP, ft_strlen(ARROW_UP)) == 0)
	{
		if (hist == NULL)
			return (0);
		if (hist->current_index > 0)
		{
			hist->current_index--;
			if (scroll_hist(hist, buffer, cursor) != 0)
				return (1);
		}
	}
	return (0);
}

int				down_arrow_key(t_buff *buffer, t_cursor *cursor,
						t_history *hist, char *seq)
{
	if (ft_strncmp(seq, ARROW_DOWN, ft_strlen(ARROW_DOWN)) == 0)
	{
		if (hist == NULL)
			return (0);
		if (hist->current_index != hist->max_index + 1)
		{
			hist->current_index++;
			if (scroll_hist(hist, buffer, cursor) != 0)
				return (1);
		}
	}
	return (0);
}
