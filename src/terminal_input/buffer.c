/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buffer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/05/07 23:07:49 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"

static size_t	buff_realloc(t_buff *buffer)
{
	char	*temp;

	buffer->buff_size = buffer->buff_size + REALLOC_SIZE;
	temp = ft_strdup(buffer->buff);
	free(buffer->buff);
	buffer->buff = (char *)ft_memalloc(sizeof(char) * buffer->buff_size + 1);
	if (buffer->buff == NULL)
		return (1);
	ft_strcpy(buffer->buff, temp);
	free(temp);
	temp = NULL;
	return (0);
}

int				insert_char(t_buff *buffer, char c)
{
	size_t			temp;

	temp = 0;
	if (buffer == NULL || buffer->buff == NULL || c == '\0')
		return (1);
	if (buffer->buff_len != 0)
		temp = buffer->buff_len - 1;
	if (buffer->buff_len == buffer->buff_size)
		if (buff_realloc(buffer) == 1)
			return (1);
	if (ft_isprint(buffer->buff[buffer->index]))
	{
		while (temp > buffer->index)
		{
			buffer->buff[temp + 1] = buffer->buff[temp];
			temp--;
		}
		buffer->buff[temp + 1] = buffer->buff[temp];
		buffer->buff[temp] = c;
	}
	else
		buffer->buff[buffer->buff_len] = c;
	buffer->index++;
	buffer->buff_len++;
	return (0);
}

void			remove_char(t_buff *buffer)
{
	size_t		curs;

	curs = buffer->index;
	if (buffer->buff[buffer->index] == '\0')
	{
		buffer->buff_len = buffer->buff_len - 1;
		buffer->index = buffer->index - 1;
		buffer->buff[buffer->buff_len] = '\0';
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
		buffer->buff_len = buffer->buff_len - 1;
	}
}

void			remove_word(t_buff *buffer, t_cursor *cursor)
{
	size_t	i;

	i = 0;
	buffer->index = buffer->rv_start;
	if (cursor->max.x == 0)
		return ;
	cursor->current.x = ((buffer->rv_start + buffer->prompt_len) \
	% cursor->max.x);
	if (cursor->current.y == (cursor->start.y + ((buffer->rv_end \
	+ buffer->prompt_len) / cursor->max.x)))
		cursor->current.y = cursor->start.y + ((buffer->rv_start + \
		buffer->prompt_len) / cursor->max.x);
	while (buffer->rv_start > buffer->rv_end)
	{
		remove_char(buffer);
		buffer->rv_start--;
		cursor->current.x--;
		set_cursor_pos(cursor, buffer->buff_len, buffer->prompt_len);
		i++;
	}
}
