/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buffer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: Invalid date        by                #+#   #+#                 */
/*   Updated: 2020/04/06 17:28:38 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"

int		init_buffs(t_buff *buffer, t_cursor *cursor)
{
	buffer->len = 0;
	buffer->index = 0;
	buffer->rv_start = 0;
	buffer->rv_end = 0;
	buffer->copy = ft_memalloc(sizeof(char) * INPUT_BUFF_SIZE + 1);
	buffer->buff = ft_memalloc(sizeof(char) * INPUT_BUFF_SIZE + 1);
	ft_memset(cursor->cur_buff, '\0', CUR_BUFF_SIZE);
	if (buffer->buff == NULL || buffer->copy == NULL)
		return (1);
	buffer->buff_size = INPUT_BUFF_SIZE;
	buffer->copy_size = INPUT_BUFF_SIZE;
	get_cursor_pos(cursor);
	return (0);
}

int			insert_char(t_buff *buffer, char c)
{
	size_t			temp;

	temp = buffer->len - 1;
	if (buffer->len == buffer->buff_size)
		if (buff_realloc(buffer, 0, buffer->buff_size) == 1)
			return (1);
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

int		buff_realloc(t_buff *buffer, size_t len, size_t size)
{
	char	*temp;

	if (len != 0)
		buffer->copy_size = buffer->copy_size + REALLOC_SIZE;
	else
		buffer->buff_size = buffer->buff_size + REALLOC_SIZE;
	if (len != 0)
	{
		temp = ft_strdup(buffer->copy);
		free(buffer->copy);
		buffer->copy = ft_memalloc(size + REALLOC_SIZE + 1);
		ft_strncpy(buffer->copy, temp, len);
	}
	else
	{
		temp = ft_strdup(buffer->buff);
		free(buffer->buff);
		buffer->buff = ft_memalloc(size + REALLOC_SIZE + 1);
		ft_strncpy(buffer->buff, temp, buffer->len);
	}
	free(temp);
	if (buffer->buff == NULL || buffer->copy == NULL)
		return (1);
	return (0);
}
