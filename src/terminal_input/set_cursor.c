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

static void		handle_newline(t_cursor *cursor, t_buff *buffer)
{
	if (cursor->direction != 0)
	{
		if (cursor->direction == CURSOR_RIGHT &&
				buffer->buff[buffer->index - 1] == '\n')
		{
			cursor->current.x = 1;
			cursor->current.y++;
			if (cursor->current.y > cursor->max.y)
			{
				send_terminal(TERM_DOWN);
				cursor->start.y--;
				cursor->current.y--;
			}
		}
		if ((cursor->direction == CURSOR_LEFT
				&& buffer->buff[buffer->index] == '\n')
				|| cursor->direction == RM_NEWLINE)
		{
			cursor->current.y--;
			cursor->current.x = resolve_x_newline(buffer, cursor);
		}
	}
	cursor->direction = 0;
}

static void		cursor_next_line(t_cursor *cursor, size_t len,
									size_t prompt_len)
{
	if (cursor->max.x == 0)
		return ;
	if ((((len - 1 + prompt_len) / cursor->max.x) + cursor->start.y) >
	cursor->max.y)
	{
		send_terminal(TERM_DOWN);
		cursor->start.y--;
		cursor->current.y--;
	}
	if (cursor->current.x > cursor->max.x)
	{
		cursor->current.x = 1;
		if (cursor->current.y != cursor->max.y)
			cursor->current.y++;
	}
	if (cursor->current.x == 0)
	{
		cursor->current.x = cursor->max.x;
		if (cursor->current.y != cursor->start.y)
			cursor->current.y--;
	}
}

void			set_cursor_pos(t_cursor *cursor, t_buff *buffer)
{
	if (buffer == NULL || buffer->buff == NULL || cursor == NULL
		|| buffer->prompt == NULL)
		return ;
	if (g_signal_handler == SIG_WINDOW)
	{
		send_terminal("rc");
		send_terminal("cd");
		get_winsize(cursor, buffer->prompt_len);
		cursor->current.x = ((buffer->prompt_len + buffer->index)
								% cursor->max.x);
		cursor->current.y = (((buffer->prompt_len + buffer->index)
								/ cursor->max.x) + cursor->start.y);
	}
	handle_newline(cursor, buffer);
	cursor_next_line(cursor, buffer->buff_len, buffer->prompt_len);
	ft_memset(&cursor->cur_buff, '\0', CUR_BUFF_SIZE);
	if (cursor->current.x < buffer->prompt_len &&
			cursor->current.y == cursor->start.y)
		cursor->current.x = buffer->prompt_len;
	if (cursor->current.x > (buffer->buff_len + buffer->prompt_len) &&
			cursor->current.y == cursor->start.y)
		cursor->current.x = buffer->buff_len + buffer->prompt_len;
	ft_snprintf(cursor->cur_buff, CUR_BUFF_SIZE, "%c[%d;%dH", ESCAPE_KEY \
				, cursor->current.y, cursor->current.x);
}
