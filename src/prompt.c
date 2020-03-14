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
#include "controls_shell.h"
#include "configure_terminal.h"

/**
 * this funciton has to make sure that the printing of the buffer (to a newline)
 * in the prompt is handled correctly. 
 */

int			calculate_layer(t_buff buffer, t_cursor *cursor)
{
	int		layer;

	if (buffer.len == 0 || cursor->max.x == 0)
		layer = 0;
	else
		layer = (buffer.len + PROMPT_LEN - 1) / cursor->max.x;
	return (layer);
}

void		print_buffer(t_buff buffer, t_cursor *cursor, int layer)
{
	int		i;

	i = 1;
	ft_printf("%.*s",cursor->max.x - PROMPT_LEN + 1, buffer.buff);
	while (layer >= i)
	{
		ft_printf("%.*s",cursor->max.x, &buffer.buff[(cursor->max.x * i) - PROMPT_LEN + 1]);
		i++;
	}
}

void		clear_prompt(t_cursor *cursor, int layer)
{
	while (layer != 0)
	{
		ft_printf("%c[%d;%dH", 27 , cursor->start.y + layer, 0);
		send_terminal("ce");
		layer--;
	}
	ft_printf("%c[%d;%dH", 27 , cursor->start.y, 0);
	send_terminal("ce");
}

/**
 * will refresh the current prompt line by first recovering the cursor location.
 * then it will clear to end of line to print the prompt and buffer again. 
 */
void		refresh_prompt(t_buff buffer, t_cursor *cursor)
{
	int layer;

	layer = calculate_layer(buffer, cursor);
	clear_prompt(cursor, layer);
	ft_printf("Cetush >>");
	print_buffer(buffer, cursor, layer);
	ft_printf("%c%s",27,  cursor->cur_buff);
}

int			prompt_shell(t_shell *shell)
{
	while (42)
	{
		get_winsize(shell);
		cursor_pos(&shell->cursor, shell->buffer.len);
		refresh_prompt(shell->buffer, &shell->cursor);
		if (read_input(shell) == 1)
			return (1);
	}
	return (0);
}
