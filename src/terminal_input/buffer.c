/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buffer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/04/06 17:03:13 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"

int			init_buffs(t_buff *buffer, t_cursor *cursor, const char *prompt)
{
	buffer->buff_len = 0;
	buffer->index = 0;
	buffer->rv_start = 0;
	buffer->rv_end = 0;
	buffer->state = 0;
	buffer->prompt_len = ft_strlen(prompt) + 1;
	if (buffer->prompt == NULL)
		buffer->prompt = ft_strndup(prompt, buffer->prompt_len);
	else if (prompt != NULL && ft_strcmp(prompt, buffer->prompt) != 0)
	{
		free(buffer->prompt);
		buffer->prompt = ft_strndup(prompt, buffer->prompt_len);
	}
	buffer->buff = (char *)ft_memalloc(sizeof(char) * INPUT_BUFF_SIZE + 1);
	if (buffer->copy == NULL)
		buffer->copy = (char *)ft_memalloc(sizeof(char) * INPUT_BUFF_SIZE + 1);
	ft_memset(cursor->cur_buff, '\0', CUR_BUFF_SIZE);
	if (buffer->buff == NULL || buffer->copy == NULL || buffer->prompt == NULL)
		return (1);
	buffer->buff_size = INPUT_BUFF_SIZE;
	buffer->copy_size = INPUT_BUFF_SIZE;
	get_cursor_pos(cursor, buffer->prompt_len);
	return (0);
}

int			insert_char(t_buff *buffer, char c)
{
	size_t			temp;

	temp = 0;
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

void		remove_char(t_buff *buffer)
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

void		remove_word(t_buff *buffer, t_cursor *cursor)
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

size_t		buff_realloc(t_buff *buffer)
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
