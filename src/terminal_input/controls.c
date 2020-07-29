/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:52:43 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/06/22 22:48:24 by devanando     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "prompt.h"
#include "input_handling.h"
#include "autocomplete.h"

int			return_key(t_buff *buffer, char c)
{
	if (c == RETURN_KEY)
	{
		send_terminal(TERM_DOWN);
		buffer->buff_len = 0;
		buffer->index = 0;
		buffer->state = RETURN_STATE;
	}
	return (0);
}

void		tab_key(t_shell *shell, char c)
{
	int		i;

	i = 0;
	if (c == TAB_KEY)
	{
		if (auto_complete(shell) == 2)
		{
			i = 0;
			while (i < 4)
			{
				insert_char(shell->buffer, ' ');
				shell->cursor.current.x++;
				set_cursor_pos(&shell->cursor, shell->buffer);
				i++;
			}
		}
	}
}

void		backspace_key(t_buff *buffer, t_cursor *cursor, char c)
{
	if (c == BACKSPACE)
	{
		if (buffer->rv_end != buffer->rv_start)
		{
			ft_swap_rv(buffer);
			remove_word(buffer, cursor);
		}
		else if ((cursor->current.y == cursor->start.y && \
		cursor->current.x > buffer->prompt_len) ||
		cursor->current.y != cursor->start.y)
		{
			if (buffer->buff[buffer->index - 1] == '\n')
				cursor->direction = RM_NEWLINE;
			else
			{
				cursor->current.x--;
				cursor->direction = RM_LEFT;
			}
			remove_char(buffer);
		}
	}
}

int			ctrl_d_key(char c, t_shell *shell)
{
	char	*PS1;

	if (shell == NULL || shell->buffer == NULL)
		return (0);
	PS1 = ft_getenv(shell->env, "PS1", SHELL_VAR);
	if (c == CNTRL_D && shell->buffer->buff_len == 0 &&
		(ft_strcmp(shell->buffer->prompt, PS1) == 0 ||
		ft_strcmp(shell->buffer->prompt, PROMPT_HEREDOC) == 0))
	{
		free(PS1);
		send_terminal(TERM_DOWN);
		return (1);
	}
	free(PS1);
	return (0);
}
