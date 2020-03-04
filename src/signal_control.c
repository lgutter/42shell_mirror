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

void		handle_esc_seq(char c, t_cursor *cursor, t_buff *buffer)
{
	char	seq[3];

	ft_bzero(seq, 3);
	if (c == ESCAPE)
	{
		if (read(STDIN_FILENO, &seq[0], 1) == -1)
			return ;
		if (read(STDIN_FILENO, &seq[1], 1) == -1)
			return ;
		if (seq[0] == 91 && seq[1] == 'D' && cursor->x != -1)
		{
			buffer->index--;
			cursor->x = cursor->x - 1;
		}
		if (seq[0] == 91 && seq[1] == 'C')
		{
			cursor->x = cursor->x + 1;
			buffer->index++;
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
