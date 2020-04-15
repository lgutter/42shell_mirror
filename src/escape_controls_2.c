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
#include "input_control.h"

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
