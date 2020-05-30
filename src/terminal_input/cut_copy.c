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
#include "input_handling.h"
#include "prompt.h"

static int	copy(t_buff *buffer)
{
	size_t len;

	ft_swap_rv(buffer);
	len = buffer->rv_start - buffer->rv_end;
	if (len < 1)
		return (0);
	if (len == 1)
	{
		buffer->rv_end--;
		len++;
	}
	ft_memdel((void **)&buffer->copy);
	buffer->copy = NULL;
	buffer->copy = (char *)ft_memalloc(sizeof(char) * (len + 1));
	if (buffer->copy == NULL)
		return (1);
	ft_strncpy(buffer->copy, &buffer->buff[buffer->rv_end], len);
	return (0);
}

static int	cut(t_buff *buffer, t_cursor *cursor)
{
	if (buffer->rv_end != buffer->rv_start)
	{
		if (copy(buffer) != 0)
			return (1);
		remove_word(buffer, cursor);
	}
	return (0);
}

static int	paste(t_buff *buffer, t_cursor *cursor)
{
	size_t len;

	buffer->state = INPUT_STATE;
	len = ft_strlen(buffer->copy);
	if (len == 0)
		return (0);
	ft_swap_rv(buffer);
	if (buffer->rv_start != buffer->rv_end)
		remove_word(buffer, cursor);
	if (insert_word(buffer, cursor, buffer->copy, len) != 0)
		return (1);
	return (0);
}

int			cut_copy_paste(t_buff *buffer, t_cursor *cursor, char c)
{
	if (cursor == NULL || buffer == NULL || buffer->buff == NULL)
		return (1);
	if (c == CNTRL_B)
		if (copy(buffer) != 0)
			return (1);
	if (c == CNTRL_V)
		if (paste(buffer, cursor) != 0)
			return (1);
	if (c == CNTRL_X)
		if (cut(buffer, cursor) != 0)
			return (1);
	return (0);
}
