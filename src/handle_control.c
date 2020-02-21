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

void		inser_character(char *string, char c, size_t cursor, size_t len)
{
	if (ft_isprint(string[cursor - 1]) && ft_isprint(string[cursor]))
	{
		while (len > cursor)
		{
			string[len + 1] = string[len];
			len = len - 1;
		}
		string[len] = c;
	}
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
