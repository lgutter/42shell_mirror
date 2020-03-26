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

char		*copy_cut_right_to_left(t_buff *buffer, int cut)
{
	char	*copy;
	size_t	len;

	len = buffer->rv_start - buffer->rv_end + 1;
	if (len == 0)
		return (NULL);
	copy = ft_memalloc(sizeof(char) * len + 1);
	if (copy == NULL)
		return (NULL);
	copy[len + 1] = '\0';
	ft_strncpy(copy, &buffer->buff[buffer->rv_end], len);
	if (cut == 1)
	{
		buffer->rv_start++;
		buffer->index = buffer->rv_start;
		while (buffer->rv_start > buffer->rv_end)
		{
			remove_char(buffer);
			buffer->rv_start--;
		}
	}
	return (copy);
}

char		*copy_cut_left_to_right(t_buff *buffer, int cut)
{
	char	*copy;
	size_t	len;

	len = buffer->rv_end + 1 - buffer->rv_start;
	if (len == 0)
		return (NULL);
	copy = ft_memalloc(sizeof(char) * len + 1);
	if (copy == NULL)
		return (NULL);
	copy[len + 1] = '\0';
	buffer->rv_end++;
	buffer->index = buffer->rv_end;
	ft_strncpy(copy, &buffer->buff[buffer->rv_start], len);
	while (buffer->rv_start < buffer->rv_end)
	{
		if (cut == 1)
			remove_char(buffer);
		buffer->rv_end--;
	}
	return (copy);
}

void	copy(t_buff *buffer)
{
	if (buffer->rv_start < buffer->rv_end)
			buffer->copy = copy_cut_left_to_right(buffer, 0);
	else if (buffer->rv_start > buffer->rv_end)
			buffer->copy = copy_cut_right_to_left(buffer, 0);
}

void	cut(t_buff *buffer)
{
	if (buffer->rv_end != buffer->rv_start)
	{
		if (buffer->copy != NULL && ft_strlen(buffer->copy) > 0)
			ft_memset(buffer->copy, '\0', ft_strlen(buffer->copy));
		if (buffer->rv_start < buffer->rv_end)
			buffer->copy = copy_cut_left_to_right(buffer, 1);
		else if (buffer->rv_start > buffer->rv_end)
			buffer->copy = copy_cut_right_to_left(buffer, 1);
		buffer->rv_start = buffer->index;
		buffer->rv_end = buffer->rv_start;
	}
	else if (buffer->index != buffer->len && buffer->rv_end != buffer->rv_start)
	{
		buffer->copy = ft_memalloc(2);
		buffer->copy[1] = '\0';
		buffer->copy[0] = buffer->buff[buffer->index];
		buffer->index++;
		remove_char(buffer);
	}
}

void	paste(t_buff *buffer, t_cursor *cursor)
{
	size_t len;
	size_t i;

	i = 0;
	len = ft_strlen(buffer->copy);
	while (len > i)
	{
		insert_char(buffer, buffer->copy[i]);
		cursor->current.x++;
		set_cursor_pos(cursor, buffer->len);
		i++;
	}
}

void	cut_copy_paste(t_buff *buffer, t_cursor *cursor, char *seq, char c)
{
	if (c == CNTRL_X)
		copy(buffer);
	if (c == CNTRL_V || (seq != NULL 
	&& ft_strncmp(seq, CNTRL_RIGHT, sizeof(CNTRL_RIGHT)) == 0))
		paste(buffer, cursor);
	if (seq != NULL && ft_strncmp(seq, CNTRL_LEFT, sizeof(CNTRL_LEFT)) == 0)
	{
		if (buffer->rv_start < buffer->rv_end)
			cursor->current.x = cursor->current.x - (buffer->rv_end \
			- buffer->rv_start);
		cut(buffer);
	}
}