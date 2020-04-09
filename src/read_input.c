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
		if (insert_char(buffer, c) > 0)
			return (1);
		cursor->current.x++;
	}
	if (c == CNTRL_R)
	{
		cursor->current.y = cursor->current.y - cursor->start.y;
		cursor->start.y = 1;
		send_terminal("cl");
	}
	if (cut_copy_paste(buffer, cursor, NULL, c) != 0)
		return (1);
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
	shell->buffer->len = ft_strlen(shell->buffer->buff);
	ret = read(STDIN_FILENO, &c, 1);
	if (ret == -1)
		return (2);
	if (ret == 1)
	{
		ret = read_esc_seq(c, &shell->cursor, shell->buffer);
		if (ret != 0)
			return(ret);
		if (handle_control_char(shell->buffer, &shell->cursor, c) != 0)
			return (1);
	}
	return (0);
}

int		read_esc_seq(char c, t_cursor *cursor, t_buff *buffer)
{
	char	seq[ESC_SEQ_SIZE];
	int		ret;

	ft_bzero(seq, ESC_SEQ_SIZE);
	if (c == ESCAPE)
	{
		ret = read(STDIN_FILENO, seq, ESC_SEQ_SIZE);
		if (ret == -1)
			return (2);
		//ft_printf("\n\nseq = %s \n", seq);
		if (cut_copy_paste(buffer, cursor, seq, 0) != 0)
			return (1);
		shift_right_key(buffer, cursor, seq);
		shift_left_key(buffer, cursor, seq);
		left_arrow_key(buffer, cursor, seq);
		right_arrow_key(buffer, cursor, seq);
		home_key(buffer, cursor, seq);
		end_key(buffer, cursor, seq);
	}
	return (0);
}
