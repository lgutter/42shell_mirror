/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   escape_controls_3.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/23 19:40:29 by devan         #+#    #+#                 */
/*   Updated: 2020/05/23 19:40:29 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"

void		cntrl_left(t_buff *buffer, t_cursor *cursor, char *seq)
{
	if (ft_strcmp(seq, CNTRL_LEFT) == 0 && buffer->index > 1)
	{
		if (!ft_isspace((int)buffer->buff[buffer->index]) &&
			ft_isspace((int)buffer->buff[buffer->index - 1]))
		{
			buffer->index--;
			cursor->current.x--;
			set_cursor_pos(cursor, buffer->buff_len, buffer->prompt_len);
		}
		while (buffer->index > 0)
		{
			if (!ft_isspace((int)buffer->buff[buffer->index]) &&
				ft_isspace((int)buffer->buff[buffer->index - 1]))
				break ;
			buffer->index--;
			cursor->current.x--;
			set_cursor_pos(cursor, buffer->buff_len, buffer->prompt_len);
		}
	}
}

void		cntrl_right(t_buff *buffer, t_cursor *cursor, char *seq)
{
	if (ft_strcmp(seq, CNTRL_RIGHT) == 0)
	{
		if (!ft_isspace((int)buffer->buff[buffer->index]) &&
			ft_isspace((int)buffer->buff[buffer->index - 1]))
		{
			buffer->index++;
			cursor->current.x++;
			set_cursor_pos(cursor, buffer->buff_len, buffer->prompt_len);
		}
		while (buffer->buff[buffer->index] != '\0')
		{
			if (!ft_isspace((int)buffer->buff[buffer->index]) &&
				ft_isspace((int)buffer->buff[buffer->index - 1]))
				break ;
			buffer->index++;
			cursor->current.x++;
			set_cursor_pos(cursor, buffer->buff_len, buffer->prompt_len);
		}
	}
}
