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

char		*cut_copy_right_to_left(t_buff *buffer, int cut)
{
	char	*copy;
	size_t	len;

	len = buffer->rv_start - buffer->rv_end;
	if (len == 1)
	{
		buffer->rv_end--;
		len = 2;
	}
	copy = ft_memalloc(sizeof(char) * len + 1);
	if (copy == NULL)
		return (NULL);
	copy[len + 1] = '\0';
	ft_strncpy(copy, &buffer->buff[buffer->rv_end], len);
	buffer->index = buffer->rv_start;
	if (cut == 1)
	{
		while (buffer->rv_start > buffer->rv_end)
		{
			remove_char(buffer);
			buffer->rv_start--;
		}
	}
	return (copy);
}

char		*cut_copy_left_to_right(t_buff *buffer, t_cursor *cursor, int cut)
{
	char	*copy;
	size_t	len;

	len = buffer->rv_end + 1 - buffer->rv_start;
	copy = ft_memalloc(sizeof(char) * len + 1);
	if (copy == NULL)
		return (NULL);
	copy[len + 1] = '\0';
	buffer->index = buffer->rv_end + 1;
	ft_strncpy(copy, &buffer->buff[buffer->rv_start], len);
	while (buffer->rv_start < buffer->rv_end)
	{
		if (cut == 1)
		{
			remove_char(buffer);
			cursor->current.x--;
		}
		buffer->rv_end--;
	}
	if (cut == 1)
		remove_char(buffer);
	return (copy);
}

void	cut_cntrl_left(t_buff *buffer,t_cursor *cursor, char *seq)
{
	if (ft_strncmp(CNTRL_LEFT, seq, sizeof(CNTRL_LEFT)) == 0 && \
		buffer->rv_end != buffer->rv_start)
	{
		if (buffer->copy != NULL && ft_strlen(buffer->copy) > 0)
			ft_memset(buffer->copy, '\0', ft_strlen(buffer->copy));
		if (buffer->rv_start < buffer->rv_end)
			buffer->copy = cut_copy_left_to_right(buffer, cursor, 1);
		else if (buffer->rv_start > buffer->rv_end)
			buffer->copy = cut_copy_right_to_left(buffer, 1);
		buffer->rv_start = buffer->index;
		buffer->rv_end = buffer->rv_start;
	}
	else if (ft_strncmp(CNTRL_LEFT, seq, sizeof(CNTRL_LEFT)) == 0 \
	&& buffer->index != buffer->len)
	{
		buffer->copy = ft_memalloc(2);
		buffer->copy[1] = '\0';
		buffer->copy[0] = buffer->buff[buffer->index];
		buffer->index++;
		remove_char(buffer);
	}
}