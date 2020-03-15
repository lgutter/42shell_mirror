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
#include "input_control.h"

int			handle_control_char(t_buff *buffer, t_cursor *cursor, char c)
{
	if (ft_isprint(c) != 0)
	{
		if (c == 'q')
			return (1);
		insert_char(buffer, c);
		cursor->current.x++;
	}
	handle_return(buffer, cursor, c);
	handle_tab(buffer, cursor, c);
	handle_backspace(buffer, cursor, c);
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
		read_esc_seq(c, &shell->cursor, &shell->buffer);
		if (handle_control_char(&shell->buffer, &shell->cursor, c) == 1)
			return (1);
	}
	return (0);
}

void		read_esc_seq(char c, t_cursor *cursor, t_buff *buffer)
{
	char	seq[3];

	ft_bzero(seq, 3);
	if (c == ESCAPE)
	{
		if (read(STDIN_FILENO, &seq[0], 1) == -1)
			return ;
		if (read(STDIN_FILENO, &seq[1], 1) == -1)
			return ;
		if (seq[0] == 91 && seq[1] == 'D' && cursor->current.x > 0)
		{
			if (buffer->index != 0)
			{
				buffer->index--;
				cursor->current.x--;
			}
		}
		if (seq[0] == 91 && seq[1] == 'C')
		{
			if (buffer->index < buffer->len)
			{
				cursor->current.x++;
				buffer->index++;
			}
		}
	}
}
