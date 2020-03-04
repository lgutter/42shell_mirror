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
		ft_printf("\noutput: %s", buffer->buff);
		ft_memset(&buffer->buff, '\0', buffer->len);
		buffer->len = 0;
		cursor->x = PROMPT_LEN;
		send_terminal("do");
	}
	handle_tab(c, buffer, cursor);
	if (c == BACKSPACE)
		remove_char(buffer);
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
		cursor_pos(shell);
	}
	return (0);
}
