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
	if (buffer == NULL || buffer->buff == NULL || buffer->prompt_len == 0 ||
		cursor == NULL || word == NULL)
		return (1);
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

void	remove_buff(t_buff *buffer, t_cursor *cursor)
{
	if (buffer != NULL && buffer->buff != NULL)
	{
		ft_memset(buffer->buff, '\0', buffer->buff_len);
		cursor->current.x = cursor->start.x;
		cursor->current.y = cursor->start.y;
		buffer->index = 0;
		buffer->buff_len = 0;
	}
}

void	free_buffer_buffs(t_shell *shell, size_t with_copy)
{
	if (shell != NULL && shell->buffer != NULL)
	{
		if (shell->buffer->prompt != NULL)
			free(shell->buffer->prompt);
		if (shell->buffer->buff != NULL)
			free(shell->buffer->buff);
		if (shell->buffer->copy != NULL && with_copy == 1)
			free(shell->buffer->copy);
		shell->buffer->copy = NULL;
		shell->buffer->buff = NULL;
	}
}
