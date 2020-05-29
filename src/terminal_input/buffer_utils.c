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

size_t		insert_word(t_buff *buffer, t_cursor *cursor, char *word,
							size_t len)
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
		if (word[i] == '\n')
		{
			cursor->current.x = 1;
			cursor->new_line = 1;
		}
		else
			cursor->current.x++;
		cursor->direction = CURSOR_RIGHT;
		set_cursor_pos(cursor, buffer);
		i++;
	}
	return (0);
}

void		remove_buff(t_buff *buffer, t_cursor *cursor)
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

void		free_buffer_buffs(t_shell *shell, size_t with_copy)
{
	if (shell != NULL && shell->buffer != NULL)
	{
		if (shell->buffer->prompt != NULL)
			free(shell->buffer->prompt);
		shell->buffer->prompt = NULL;
		if (shell->buffer->buff != NULL)
			free(shell->buffer->buff);
		shell->buffer->buff = NULL;
		if (shell->buffer->copy != NULL && with_copy == 1)
		{
			free(shell->buffer->copy);
			shell->buffer->copy = NULL;
		}
	}
}

static void	parse_cursor_pos(t_cursor *cursor, char *pos, size_t prompt_len
							, int ret)
{
	int		temp;

	temp = ft_atoi(&pos[2]);
	if (temp != 0)
		cursor->start.y = temp;
	while (ft_isdigit(pos[ret]) == 0)
		ret = ret - 1;
	while (ft_isdigit(pos[ret - 1]) == 1)
		ret = ret - 1;
	cursor->current.x = ft_atoi(&pos[ret]);
	if (cursor->current.x > 1)
	{
		cursor->start.y++;
		cursor->new_line_x = cursor->current.x;
	}
	else
		cursor->start.x = prompt_len;
}

void		get_cursor_pos(t_cursor *cursor, size_t prompt_len)
{
	char	pos[16];
	int		ret;

	send_terminal("sc");
	ft_printf("%c[6n", ESCAPE_KEY);
	ft_memset(&pos, '\0', sizeof(pos));
	ret = read(STDIN_FILENO, &pos, sizeof(pos));
	if (ret == -1)
		return ;
	if (ret < 3)
		read(STDIN_FILENO, &pos, sizeof(pos));
	else
		parse_cursor_pos(cursor, pos, prompt_len, ret);
	cursor->current.x = prompt_len;
	cursor->current.y = cursor->start.y;
}
