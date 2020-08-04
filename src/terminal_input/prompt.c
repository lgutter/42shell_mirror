/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:52:43 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/08/04 17:05:26 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "prompt.h"
#include "history.h"
#include "input_handling.h"
#include "signal_handler.h"
#include "environment.h"

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

static void		refresh_prompt(t_buff *buffer, t_cursor *cursor)
{
	if (cursor->new_line_x > 1)
	{
		ft_printf("%c[%d;%dH", ESCAPE_KEY, cursor->start.y - 1,
			cursor->new_line_x);
		ft_printf("%s%%%s", RV_MODE, RV_RESET);
		ft_printf("%c[%d;%dH", ESCAPE_KEY, cursor->start.y, cursor->start.x);
		cursor->new_line_x = 1;
	}
	ft_printf("%c[%d;%dH", ESCAPE_KEY, cursor->start.y, 0);
	send_terminal("cd");
	ft_printf("%s", buffer->prompt);
	print_buffer(buffer);
	ft_printf("%s", cursor->cur_buff);
}

static int		init_buffs(t_buff *buffer, t_cursor *cursor, const char *prompt)
{
	buffer->buff_len = 0;
	buffer->index = 0;
	buffer->rv_start = 0;
	buffer->rv_end = 0;
	buffer->state = 0;
	buffer->prompt_len = ft_strlen(prompt) + 1;
	buffer->prompt = ft_strndup(prompt, buffer->prompt_len);
	if (prompt == NULL)
		return (1);
	if (ft_strcmp(prompt, PROMPT_NORMAL_COLOUR) == 0)
		buffer->prompt_len = PROMPT_COLOUR_LEN;
	buffer->buff = (char *)ft_memalloc(sizeof(char) * (INP_BUFF_SIZE + 1));
	if (buffer->copy == NULL)
		buffer->copy = (char *)ft_memalloc(sizeof(char) * (INP_BUFF_SIZE + 1));
	cursor->max = (t_point){40, 40};
	cursor->start = (t_point){1, 1};
	ft_memset(cursor->cur_buff, '\0', CUR_BUFF_SIZE);
	if (buffer->buff == NULL || buffer->copy == NULL)
		return (1);
	buffer->buff_size = INP_BUFF_SIZE;
	buffer->copy_size = INP_BUFF_SIZE;
	get_winsize(cursor, buffer->prompt_len);
	return (0);
}

static char		*interactive_prompt_shell(t_shell *shell, const char *prompt)
{
	char *temp;

	temp = NULL;
	if (init_buffs(shell->buffer, &shell->cursor, prompt) == 1)
		return (NULL);
	while (shell->buffer->state != RETURN_STATE)
	{
		set_cursor_pos(&shell->cursor, shell->buffer);
		refresh_prompt(shell->buffer, &shell->cursor);
		if (check_fds(shell) == 1 || read_input(shell) == 1)
		{
			free_buffer_buffs(shell, 1);
			return (NULL);
		}
		shell->buffer->buff_len = ft_strlen(shell->buffer->buff);
	}
	shell->buffer->state = INPUT_STATE;
	temp = ft_strndup(shell->buffer->buff, shell->buffer->buff_size);
	free_buffer_buffs(shell, 0);
	return (temp);
}

char			*prompt_shell(t_shell *shell, const char *prompt)
{
	char	*temp;

	temp = NULL;
	if (shell != NULL && prompt != NULL && shell->buffer != NULL)
	{
		if (shell->interactive == true)
		{
			temp = interactive_prompt_shell(shell, prompt);
		}
		else
		{
			if (get_next_line(STDIN_FILENO, &temp) == 0)
			{
				free(temp);
				temp = NULL;
			}
		}
	}
	return (temp);
}
