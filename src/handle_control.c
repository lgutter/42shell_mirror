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

void		handle_esc_seq(char c, t_cursor *cursor)
{
	char	seq[3];

	ft_bzero(seq, 3);
	if (c == ESCAPE)
	{
		read(STDIN_FILENO, &seq[0], 1);
		read(STDIN_FILENO, &seq[1], 1);
		if (seq[0] == 91 && seq[1] == 'D')
			cursor->x = cursor->x - 1;
		if (seq[0] == 91 && seq[1] == 'C')
			cursor->x = cursor->x + 1;
	}
}

int			insert_char(t_buff *buffer, t_cursor *cursor, char c)
{
	size_t 			temp;

	temp = buffer->len;
	if (ft_isprint(buffer->buff[cursor->x]) && ft_isprint(buffer->buff[cursor->x + 1]))
	{
		while (temp > cursor->x)
		{
			buffer->buff[temp + 1] = buffer->buff[temp];
			temp--;
		}
		buffer->buff[temp] = c;
		buffer->len = buffer->len + 1;

		return (1);
	}
	return (0);
}

void		handle_backspace(char c, t_buff *buffer, t_cursor *cursor)
{
	if (c == BACKSPACE && buffer->len > 0 && buffer->buff[buffer->len] == '\0')
	{
		ft_printf("\ntest =  %c\n", buffer->buff[buffer->len - 1]);
		buffer->len = buffer->len - 1;
		cursor->x = cursor->x - 1;
		buffer->buff[buffer->len] = '\0';
	}
}

void		handle_tab(char c, t_buff *buffer, t_cursor *cursor)
{
	if (c == TAB)
	{
		buffer->buff[buffer->len] = '\t';
		buffer->len = buffer->len + 1;
		cursor->x = cursor->x + 1;
	}
}
