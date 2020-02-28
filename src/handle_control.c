/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_control.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: Invalid date        by                #+#    #+#                */
/*   Updated: 0003/01/01 00:00:00 by               ########   odam.nl         */
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
		if (read(STDIN_FILENO, &seq[0], 1) == -1)
			return ;
		if (read(STDIN_FILENO, &seq[1], 1) == -1)
			return ;
		if (seq[0] == 91 && seq[1] == 'D')
		{
			if (cursor->x > 0)
				cursor->x = cursor->x - 1;
			else
			{
				cursor->x = cursor->x_max;
				cursor->y--;
				cursor->layer--;
			}
		}
		if (seq[0] == 91 && seq[1] == 'C')
		{
			if (cursor->x < cursor->x_max)
				cursor->x = cursor->x + 1;
			else
			{
				cursor->y++;
				cursor->x = 0;
			}
		}
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
		if (buffer->buff[cursor->x] == '\0')
		{
			buffer->len = buffer->len - 1;
			cursor->x = cursor->x - 1;
			buffer->buff[buffer->len] = '\0';
		}
		else if (cursor->x > 0)
		{
			cursor->x = cursor-> x;
			curs = cursor->x;
			//ft_printf("\n test (%c)\n", buffer->buff[cursor->x - 1]);
			while(buffer->buff[cursor->x] != '\0')
			{
				buffer->buff[cursor->x] = buffer->buff[cursor->x + 1];
				cursor->x = cursor->x + 1;
			}
			buffer->buff[cursor->x] = '\0';
			cursor->x = curs;
			buffer->len = buffer->len - 1;
		}
	}
}

void		handle_tab(char c, t_buff *buffer, t_cursor *cursor)
{
	int		i;

	i = 0;
	if (c == TAB)
	{
		// autocomplete
		while (i != 4)
		{
			buffer->buff[buffer->len] = ' ';
			buffer->len = buffer->len + 1;
			cursor->x = cursor->x + 1;
			i++;
		}
	}
}
