/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:52:43 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/04/14 11:52:43 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"
#include "history.h"

static void		print_buffer(t_buff *buffer)
{
	if (buffer->rv_end > buffer->rv_start)
	{
		ft_printf("%.*s%s", buffer->rv_start, buffer->buff, RV_MODE);
		ft_printf("%.*s", buffer->rv_end - buffer->rv_start,
		&buffer->buff[buffer->rv_start]);
		ft_printf("%s%s", RV_RESET, &buffer->buff[buffer->rv_end]);
	}
	else if (buffer->rv_end < buffer->rv_start)
	{
		ft_printf("%.*s%s", buffer->rv_end, buffer->buff, RV_MODE);
		ft_printf("%.*s", buffer->rv_start - buffer->rv_end,
		&buffer->buff[buffer->rv_end]);
		ft_printf("%s%s", RV_RESET, &buffer->buff[buffer->rv_start]);
	}
	else
		ft_printf("%s", buffer->buff);
}

static void		clear_prompt(t_cursor *cursor)
{
	ft_printf("%c[%d;%dH", ESCAPE, cursor->start.y, 0);
	send_terminal("cd");
}

static void		refresh_prompt(t_buff *buffer, t_cursor *cursor)
{
	clear_prompt(cursor);
	ft_printf("%s", buffer->prompt);
	print_buffer(buffer);
	ft_printf("%s", cursor->cur_buff);
}

char			*prompt_shell(t_shell *shell, const char *prompt)
{
	char	*temp;

	if (init_buffs(shell->buffer, &shell->cursor, prompt) == 1)
		return (NULL);
	while (shell->buffer->state != RETURN_STATE)
	{
		get_winsize(shell);
		set_cursor_pos(&shell->cursor, shell->buffer->buff_len,
		shell->buffer->prompt_len);
		refresh_prompt(shell->buffer, &shell->cursor);
		if (read_input(shell) == 1)
		{
			free(shell->buffer->buff);
			if (shell->buffer->copy != NULL)
				free(shell->buffer->copy);
			shell->buffer->copy = NULL;
			shell->buffer->buff = NULL;
			return (NULL);
		}
	}
	shell->buffer->state = INPUT_STATE;
	temp = ft_strndup(shell->buffer->buff, shell->buffer->buff_size);
	free(shell->buffer->buff);
	shell->buffer->buff = NULL;
	return (temp);
}
