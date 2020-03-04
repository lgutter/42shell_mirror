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

void		refresh_prompt(t_buff buffer, t_cursor cursor)
{
	ft_printf("%c[%d;%dH", 27, cursor.y, 0);
	send_terminal("ce");
	send_terminal("up");
	ft_printf("\nCetush >>%s", buffer.buff);
	ft_printf("%s", cursor.cur_buff);
}

int			prompt_shell(t_shell *shell)
{
	while (42)
	{
		refresh_prompt(shell->buffer, shell->cursor);
		if (read_input(shell) == 1)
			return (1);
	}
	return (0);
}
