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

void		init_buffs(t_shell *shell)
{
	shell->buffer->len = 0;
	shell->buffer->index = 0;
	shell->buffer->rv_start = 0;
	shell->buffer->rv_end = 0;
	shell->buffer->copy = NULL;
	ft_memset(&shell->buffer->buff, '\0', INPUT_BUFF_SIZE);
	ft_memset(&shell->cursor.cur_buff, '\0', CUR_BUFF_SIZE);
	get_cursor_pos(&shell->cursor);
}

void		insert_char(t_buff *buffer, char c)
{
	size_t			temp;
	size_t			curs;

	curs = buffer->index;
	temp = buffer->len - 1;
	if (ft_isprint(buffer->buff[curs]) && ft_isprint(buffer->buff[curs]))
	{
		while (temp != curs)
		{
			buffer->buff[temp + 1] = buffer->buff[temp];
			temp--;
		}
		buffer->buff[temp + 1] = buffer->buff[temp];
		buffer->buff[temp] = c;
	}
	else
		buffer->buff[buffer->len] = c;
	buffer->index++;
	buffer->len = buffer->len + 1;
}

void		remove_char(t_buff *buffer)
{
	size_t		curs;

	curs = buffer->index;
	if (buffer->buff[buffer->index] == '\0')
	{
		buffer->len = buffer->len - 1;
		buffer->index = buffer->index - 1;
		buffer->buff[buffer->len] = '\0';
	}
	else if (buffer->index != 0)
	{
		curs = buffer->index;
		while (buffer->buff[buffer->index - 1] != '\0')
		{
			buffer->buff[buffer->index - 1] = buffer->buff[buffer->index];
			buffer->index = buffer->index + 1;
		}
		buffer->buff[buffer->index - 1] = '\0';
		buffer->index = curs - 1;
		buffer->len = buffer->len - 1;
	}
}
