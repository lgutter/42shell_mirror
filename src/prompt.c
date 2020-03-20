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

size_t			calculate_layer(t_buff buffer, t_cursor *cursor)
{
	size_t		layer;

	if (buffer.len == 0 || cursor->max.x == 0)
		layer = 0;
	else
		layer = (buffer.len + PROMPT_LEN - 1) / cursor->max.x;
	return (layer);
}

static void		print_buffer(t_buff buffer, t_cursor *cursor, int layer)
{
	int		i;

	i = 1;
	ft_printf("%.*s",cursor->max.x - PROMPT_LEN + 1, buffer.buff);
	while (layer >= i)
	{
		ft_printf("%.*s",cursor->max.x, &buffer.buff[(cursor->max.x * i)	\
		 - PROMPT_LEN + 1]);
		i++;
	}
}

static void		clear_prompt(t_cursor *cursor)
{
	ft_printf("%c[%d;%dH", ESCAPE , cursor->start.y, 0);
	send_terminal("cd");
}

static void		refresh_prompt(t_buff buffer, t_cursor *cursor)
{
	size_t layer;

	layer = calculate_layer(buffer, cursor);
	clear_prompt(cursor);
	ft_printf("%s", PROMPT_STR);
	print_buffer(buffer, cursor, layer);
	ft_printf("%s",  cursor->cur_buff);
}


int			prompt_shell(t_shell *shell)
{
	while (42)
	{
		get_winsize(shell);
		set_cursor_pos(&shell->cursor, shell->buffer->len);
		refresh_prompt(*shell->buffer, &shell->cursor);
		if (read_input(shell) == 1)
			return (1);
	}
	return (0);
}
