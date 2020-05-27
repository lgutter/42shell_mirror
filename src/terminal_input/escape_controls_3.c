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

static void		cntrl_left(t_buff *buffer, t_cursor *cursor, char *seq)
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

static void		cntrl_right(t_buff *buffer, t_cursor *cursor, char *seq)
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

static void		cntrl_up(t_buff *buffer, t_cursor *cursor, char *seq)
{
	if (ft_strcmp(seq, CNTRL_UP) == 0 && cursor->current.y > cursor->start.y)
	{
		cursor->current.y--;
		if (cursor->current.y == cursor->start.y &&
			cursor->current.x < buffer->prompt_len)
			cursor->current.x = cursor->start.x;
	}
}

static void		cntrl_down(t_buff *buffer, t_cursor *cursor, char *seq)
{
	size_t		temp;

	if (ft_strcmp(seq, CNTRL_DOWN) == 0 && cursor->current.y < cursor->max.x)
	{
		cursor->current.y++;
		if (cursor->current.y == cursor->max.y)
		{
			temp = (buffer->buff_len + buffer->prompt_len) / cursor->max.x;
			if (cursor->current.x > temp)
				cursor->current.x = temp;
		}
	}
}

void			handle_cntrl_arrows(t_buff *buffer, t_cursor *cursor, char *seq)
{
	cntrl_left(buffer, cursor, seq);
	cntrl_right(buffer, cursor, seq);
	cntrl_up(buffer, cursor, seq);
	cntrl_down(buffer, cursor, seq);
}
