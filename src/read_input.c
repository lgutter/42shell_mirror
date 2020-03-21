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
	//ft_printf("\n\n (%d)\n", c);
	if (ft_isprint(c) != 0)
	{
		if (c == 'q')
			return (1);
		if (c == '=')
			ft_printf("\n");
		insert_char(buffer, c);
		cursor->current.x++;
	}
	if (c == CNTRL_R)
	{
		cursor->start.x = 1;
		cursor->start.y = 1;
		cursor->current.y = 1;
		send_terminal("cl");
	}
	return_key(buffer, cursor, c);
	tab_key(buffer, cursor, c);
	backspace_key(buffer, cursor, c);
	return (0);
}

int			read_input(t_shell *shell)
{
	char		c;
	int			ret;

	c = '\0';
	ret = read(STDIN_FILENO, &c, 1);
	if (ret == -1)
		ft_dprintf(2, "ERROR");
	if (ret == 1)
	{
		read_esc_seq(c, &shell->cursor, shell->buffer);
		if (handle_control_char(shell->buffer, &shell->cursor, c) == 1)
			return (1);
	}
	return (0);
}

void		read_esc_seq(char c, t_cursor *cursor, t_buff *buffer)
{
	char	seq[ESC_SEQ_SIZE];
	int		ret;

	ft_bzero(seq, ESC_SEQ_SIZE);
	if (c == ESCAPE)
	{
		ret = read(STDIN_FILENO, seq, ESC_SEQ_SIZE);
		if (ret == -1)
			return ;
		//ft_printf("\n\nseq = %s \n", seq);
		cut_cntrl_left(buffer, cursor, seq);
		shift_right_key(buffer, cursor, seq);
		shift_left_key(buffer, cursor, seq);
		left_arrow_key(buffer, cursor, seq);
		right_arrow_key(buffer, cursor, seq);
		home_key(buffer, cursor, seq);
		end_key(buffer, cursor, seq);
	}
}
