/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cut_copy.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:52:43 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/04/14 11:52:43 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"

int		copy(t_buff *buffer)
{
	size_t len;

	ft_swap_rv(buffer);
	len = buffer->rv_start - buffer->rv_end;
	if (len == 1)
	{
		buffer->rv_end--;
		len++;
	}
	while (len > buffer->copy_size)
		if (buff_realloc(buffer, len, buffer->copy_size) == 1)
			return (1);
	ft_memset(buffer->copy, '\0', buffer->copy_size);
	ft_strncpy(buffer->copy, &buffer->buff[buffer->rv_end], len);
	return (0);
}

int		cut(t_buff *buffer, t_cursor *cursor)
{
	if (buffer->rv_end != buffer->rv_start)
	{
		if (copy(buffer) != 0)
			return (1);
		remove_word(buffer, cursor);
	}
	return (0);
}

int		paste(t_buff *buffer, t_cursor *cursor)
{
	size_t len;
	size_t i;

	i = 0;
	len = ft_strlen(buffer->copy);
	if (len == 0)
		return (0);
	ft_swap_rv(buffer);
	if (buffer->rv_start != buffer->rv_end)
		remove_word(buffer, cursor);
	while (len > i)
	{
		if (insert_char(buffer, buffer->copy[i]) != 0)
			return (1);
		cursor->current.x++;
		set_cursor_pos(cursor, buffer->len);
		i++;
	}
	return (0);
}

int		cut_copy_paste(t_buff *buffer, t_cursor *cursor, char *seq, char c)
{
	if (c == CNTRL_X)
		if (copy(buffer) != 0)
			return (1);
	if (c == CNTRL_V || (seq != NULL
	&& ft_strncmp(seq, CNTRL_RIGHT, sizeof(CNTRL_RIGHT)) == 0))
		if (paste(buffer, cursor) != 0)
			return (1);
	if (seq != NULL && ft_strncmp(seq, CNTRL_LEFT, sizeof(CNTRL_LEFT)) == 0)
		if (cut(buffer, cursor) != 0)
			return (1);
	return (0);
}
