/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_cursor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:35:25 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/05/18 12:43:00 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "prompt.h"
#include "signal_handler.h"

static size_t	resolve_x_newline(t_buff *buffer, t_cursor *cursor)
{
	size_t i;
	size_t start;

	i = buffer->index;
	start = 0;
	while (i > 0)
	{
		i--;
		start++;
		if (buffer->buff[i] == '\n')
			break ;
	}
	if (cursor->current.y == cursor->start.y)
		return (buffer->prompt_len + start);
	else
		return (start);
}

static void		change_cursor_x(t_cursor *cursor, t_buff *buffer)
{
	if (cursor->direction == CURSOR_RIGHT)
	{
		if (buffer->buff[buffer->index - 1] == '\n')
			cursor->current.x = cursor->max.x + 1;
		else
			cursor->current.x++;
	}
	if (cursor->direction == CURSOR_LEFT || cursor->direction == RM_NEWLINE)
	{
		cursor->current.x--;
		if (buffer->buff[buffer->index] == '\n' ||
				cursor->direction == RM_NEWLINE)
		{
			cursor->current.y--;
			cursor->current.x = resolve_x_newline(buffer, cursor);
		}
	}
	cursor->direction = 0;
}

void			change_cursor(t_cursor *cursor, t_buff *buffer)
{
	if (cursor->max.x == 0 || cursor->max.y == 0)
		return ;
	change_cursor_x(cursor, buffer);
	if (cursor->current.x <= 0)
	{
		cursor->current.x = cursor->max.x;
		cursor->current.y--;
	}
	if (cursor->current.x > cursor->max.x)
	{
		cursor->current.y++;
		cursor->current.x = 1;
	}
	if (cursor->current.y > cursor->max.y || (((buffer->buff_len - 1 +
		buffer->prompt_len) / cursor->max.x) + cursor->start.y) > cursor->max.y)
	{
		cursor->start.y--;
		cursor->current.y--;
		cursor->scroll = 1;
	}
	if (cursor->current.y < cursor->start.y)
		cursor->current.y = cursor->start.y;
}

void			set_cursor_pos(t_cursor *cursor, t_buff *buffer)
{
	if (buffer == NULL || buffer->buff == NULL || cursor == NULL
		|| buffer->prompt == NULL)
		return ;
	if (cursor->scroll == 1)
	{
		send_terminal(TERM_DOWN);
		cursor->scroll = 0;
	}
	if ((g_signal_handler & SIG_WINDOW) == SIG_WINDOW)
	{
		send_terminal("rc");
		send_terminal("cd");
		get_winsize(cursor, buffer->prompt_len);
		cursor->current.x = ((buffer->prompt_len + buffer->index)
								% cursor->max.x);
		cursor->current.y = (((buffer->prompt_len + buffer->index)
								/ cursor->max.x) + cursor->start.y);
		g_signal_handler &= ~SIG_WINDOW;
	}
	ft_memset(&cursor->cur_buff, '\0', CUR_BUFF_SIZE);
	ft_snprintf(cursor->cur_buff, CUR_BUFF_SIZE, "%c[%d;%dH", ESCAPE_KEY \
				, cursor->current.y, cursor->current.x);
}
