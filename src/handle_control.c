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
	size_t			temp;
	size_t			curs;

	curs = cursor->x - PROMPT_LEN;
	temp = buffer->len - 1;
	if (ft_isprint(buffer->buff[curs]) && ft_isprint(buffer->buff[curs]))
	{
		while (temp != curs)
		{
			buffer->buff[temp + 1] = buffer->buff[temp];
			temp--;
		}
		buffer->buff[temp + 1] = buffer->buff[temp];
		buffer->len = buffer->len + 1;
		cursor->x = cursor->x + 1;
		buffer->buff[temp] = c;
		return (1);
	}
	return (0);
}

void		handle_backspace(char c, t_buff *buffer, t_cursor *cursor)
{
	size_t		curs;

	curs = cursor->x - PROMPT_LEN;
	if (c == BACKSPACE && buffer->len > 0)
	{
		ft_printf("\ntesting %c", buffer->buff[curs]);
		if (buffer->buff[curs] == '\0')
		{
			buffer->len = buffer->len - 1;
			cursor->x = cursor->x - 1;
			buffer->buff[buffer->len] = '\0';
		}
		else
		{
			ft_printf("\ntesting");
		}
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
