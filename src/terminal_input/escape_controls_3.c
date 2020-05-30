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
#include "prompt.h"
#include "input_handling.h"

static void		cntrl_left(t_buff *buffer, t_cursor *cursor, char *seq)
{
	if (ft_strcmp(seq, CNTRL_LEFT) == 0 && buffer->index > 1)
	{
		if (!ft_isspace((int)buffer->buff[buffer->index]) &&
			ft_isspace((int)buffer->buff[buffer->index - 1]))
		{
			buffer->index--;
			cursor->current.x--;
			cursor->direction = CURSOR_LEFT;
			set_cursor_pos(cursor, buffer);
		}
		while (buffer->index > 0)
		{
			if (!ft_isspace((int)buffer->buff[buffer->index]) &&
				ft_isspace((int)buffer->buff[buffer->index - 1]))
				break ;
			buffer->index--;
			cursor->current.x--;
			cursor->direction = CURSOR_LEFT;
			set_cursor_pos(cursor, buffer);
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
			cursor->direction = CURSOR_RIGHT;
			set_cursor_pos(cursor, buffer);
		}
		while (buffer->buff[buffer->index] != '\0')
		{
			if (!ft_isspace((int)buffer->buff[buffer->index]) &&
				ft_isspace((int)buffer->buff[buffer->index - 1]))
				break ;
			buffer->index++;
			cursor->current.x++;
			cursor->direction = CURSOR_RIGHT;
			set_cursor_pos(cursor, buffer);
		}
	}
}

static void		cntrl_up(t_buff *buffer, t_cursor *cursor, char *seq)
{
	if (ft_strcmp(seq, CNTRL_UP) == 0 && cursor->current.y > cursor->start.y)
	{
		if (strchr(buffer->buff, '\n') != NULL)
			return ;
		cursor->current.y--;
		if (cursor->current.y == cursor->start.y &&
			cursor->current.x < buffer->prompt_len - 1)
		{
			buffer->index = 0;
			cursor->current.x = cursor->start.x;
		}
		else
			buffer->index = buffer->index - cursor->max.x;
	}
}

static void		cntrl_down(t_buff *buffer, t_cursor *cursor, char *seq)
{
	size_t		temp;

	temp = (((buffer->prompt_len + buffer->buff_len) / cursor->max.x) +
		cursor->start.y);
	if (ft_strcmp(seq, CNTRL_DOWN) == 0 && cursor->current.y < temp)
	{
		if (strchr(buffer->buff, '\n') != NULL)
			return ;
		cursor->current.y++;
		temp = (buffer->prompt_len + buffer->buff_len) % cursor->max.x;
		if (cursor->current.y == cursor->max.y && cursor->current.x > temp)
		{
			buffer->index = buffer->buff_len;
			cursor->current.x = temp;
		}
		else
			buffer->index = buffer->index + cursor->max.x;
	}
}

void			handle_cntrl_arrows(t_buff *buffer, t_cursor *cursor, char *seq)
{
	cntrl_left(buffer, cursor, seq);
	cntrl_right(buffer, cursor, seq);
	cntrl_up(buffer, cursor, seq);
	cntrl_down(buffer, cursor, seq);
}
