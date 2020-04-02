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

void	copy(t_buff *buffer)
{
	size_t len;

	ft_swap_rv(buffer);
	len = buffer->rv_start - buffer->rv_end;
	if (len == 1)
	{
		buffer->rv_end--;
		len++;
	}
	if (len == 0)
		buffer->copy = NULL;
	buffer->copy = ft_memalloc(sizeof(char) * len + 1);
	if (buffer->copy == NULL)
		return ;
	buffer->copy[len + 1] = '\0';
	ft_strncpy(buffer->copy, &buffer->buff[buffer->rv_end], len);
}

void	cut(t_buff *buffer, t_cursor *cursor)
{
	if (buffer->rv_end != buffer->rv_start)
	{
		if (buffer->copy != NULL && ft_strlen(buffer->copy) > 0)
			ft_memset(buffer->copy, '\0', ft_strlen(buffer->copy));
		copy(buffer);
		remove_word(buffer, cursor);
	}
}

void	paste(t_buff *buffer, t_cursor *cursor)
{
	size_t len;
	size_t i;

	i = 0;
	if (!buffer->copy)
		return ;
	len = ft_strlen(buffer->copy);
	ft_swap_rv(buffer);
	if (buffer->rv_start != buffer->rv_end)
		remove_word(buffer, cursor);
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
		cut(buffer, cursor);
}
