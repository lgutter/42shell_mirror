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

void		init_buffs(t_buff *buffer, t_cursor *cursor)
{
	buffer->len = 0;
	buffer->index = 0;
	buffer->rv_start = 0;
	buffer->rv_end = 0;
	buffer->copy = ft_memalloc(sizeof(char) * INPUT_BUFF_SIZE + 1);
	buffer->buff = ft_memalloc(sizeof(char) * INPUT_BUFF_SIZE + 1);
	if (buffer->buff == 0 || buffer->copy == 0)
		return;
	buffer->buff_size = INPUT_BUFF_SIZE;
	buffer->copy_size = INPUT_BUFF_SIZE;
	ft_memset(buffer->buff, '\0', INPUT_BUFF_SIZE + 1);
	ft_memset(cursor->cur_buff, '\0', CUR_BUFF_SIZE + 1);
	get_cursor_pos(cursor);
}

int			insert_char(t_buff *buffer, char c)
{
	size_t			temp;

	temp = buffer->len - 1;
	if (buffer->len == buffer->buff_size)
	{
	 	buffer->buff = buff_realloc(buffer->buff, buffer->buff_size, \
		 buffer->len);
		 if (buffer->buff == NULL)
		 	return (1);
		buffer->buff_size = buffer->buff_size + REALLOC_SIZE;
	}
	if (ft_isprint(buffer->buff[buffer->index]))
	{
		while (temp != buffer->index)
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
	buffer->len++;
	return (0);
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

void	remove_word(t_buff *buffer, t_cursor *cursor)
{
	size_t	i;

	i = 0;
	buffer->index = buffer->rv_start;
	cursor->current.x = ((buffer->rv_start + PROMPT_LEN) % cursor->max.x);
	if (cursor->current.y == (cursor->start.y + ((buffer->rv_end + PROMPT_LEN) \
	/ cursor->max.x)))
		cursor->current.y = cursor->start.y + ((buffer->rv_start + PROMPT_LEN) \
		/ cursor->max.x);
	while (buffer->rv_start > buffer->rv_end)
	{
		remove_char(buffer);
		buffer->rv_start--;
		cursor->current.x--;
		set_cursor_pos(cursor, buffer->len);
		i++;
	}
}

char	*buff_realloc(char *buffer, size_t buff_size, size_t len)
{
	char	*temp;
	size_t 	i;

	i = 0;

	buff_size = buff_size + REALLOC_SIZE;
	temp = ft_memalloc(sizeof(char) * buff_size + 1);
	if (temp == NULL)
		return (NULL);
	ft_memset(temp, '\0', buff_size + 1);
	while (i < len)
	{
		temp[i] = buffer[i];
		i++;
	}
	free(buffer);
	return (temp);
}