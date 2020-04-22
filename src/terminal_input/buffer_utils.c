/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buffer_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/19 17:42:07 by devan         #+#    #+#                 */
/*   Updated: 2020/04/19 17:42:07 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"

size_t	insert_word(t_buff *buffer, t_cursor *cursor, char *word, size_t len)
{
	size_t	i;

	i = 0;
	while (len > i)
	{
		if (insert_char(buffer, word[i]) != 0)
			return (1);
		cursor->current.x++;
		set_cursor_pos(cursor, buffer->buff_len, buffer->prompt_len);
		i++;
	}
	cursor->current.x++;
	set_cursor_pos(cursor, buffer->buff_len, buffer->prompt_len);
	return (0);
}

void	remove_buff(t_buff *buffer, t_cursor *cursor, t_history *hist)
{
	ft_memset(buffer->buff, '\0', buffer->buff_len);
	cursor->current.x = cursor->start.x;
	cursor->current.y = cursor->start.y;
	buffer->index = 0;
	buffer->buff_len = 0;
}
