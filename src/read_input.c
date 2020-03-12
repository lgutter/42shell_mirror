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

int			handle_control_char(t_buff *buffer, t_cursor *cursor, char c)
{
	if (ft_isprint(c))
	{
		//if (c == 'd')
		//	send_terminal("do");
		//if (c == 'f')
		//	send_terminal("up");
		if (c == 'p')
		{
			buffer->buff[buffer->len] = '\n';
			cursor->x = cursor->x + 1;
			buffer->len = buffer->len + 1;
		}
		if (c == 'q')
			return (1);
		insert_char(buffer, c);
		cursor->x++;
	}
	if (c == 10)
	{
		cursor->y++;
		cursor->y++;
		ft_printf("\noutput (%d): %s",cursor->y, buffer->buff);
		ft_memset(&buffer->buff, '\0', buffer->len);
		buffer->len = 0;
		cursor->x = PROMPT_LEN;
		send_terminal("do");
		//send_terminal("do");
	}
	handle_tab(c, buffer, cursor);
	if (c == BACKSPACE && cursor->x > PROMPT_LEN)
	{
		ft_printf("\n buff[i]= (%c) index= (%d) cursorx = (%d) cursory = (%d)\n", buffer->buff[buffer->index - 1], buffer->index, cursor->x, cursor->y);
		cursor->x--;
		remove_char(buffer);
	}
	return (0);
}

int			read_input(t_shell *shell)
{
	char		c;
	ssize_t		ret;

	c = '\0';
	ret = read(STDIN_FILENO, &c, 1);
	if (ret == -1)
		ft_dprintf(2, "ERROR");
	if (ret == 1)
	{
		//ft_printf("\n(%d)\n", c);
		handle_esc_seq(c, &shell->cursor, &shell->buffer);
		if (handle_control_char(&shell->buffer, &shell->cursor, c) == 1)
			return (1);
	}
	return (0);
}
