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
void		newline_buffer(t_buff buffer, t_cursor cursor)
{
	int		layer;
	int	i;

	i = 1;
	if (buffer.len == 0 || cursor.x_max == 0)
		layer = 0;
	else
		layer = (buffer.len + PROMPT_LEN - 1) / cursor.x_max;
	ft_printf("%.*s",cursor.x_max - PROMPT_LEN + 1, buffer.buff);
	while (layer >= i)
	{
		ft_printf("%.*s",cursor.x_max, &buffer.buff[(cursor.x_max * i) - PROMPT_LEN + 1]);
		i++;
	}
}

/**
 * will refresh the current prompt line by first recovering the cursor location.
 * then it will clear to end of line to print the prompt and buffer again. 
 */
void		refresh_prompt(t_buff buffer, t_cursor cursor)
{
	send_terminal("rc");
	send_terminal("ce");
	ft_printf("Cetush >>");
	newline_buffer(buffer, cursor);
	ft_printf("%s", cursor.cur_buff);
}

int			prompt_shell(t_shell *shell)
{
	while (42)
	{
		cursor_pos(shell);
		refresh_prompt(shell->buffer, shell->cursor);
		if (read_input(shell) == 1)
			return (1);
	}
	return (0);
}
