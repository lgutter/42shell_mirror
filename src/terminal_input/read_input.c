/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:52:43 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/04/14 11:52:43 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"

int			handle_control_char(t_buff *buffer, t_cursor *cursor, char c)
{
	if (ft_isprint(c) != 0)
	{
		buffer->state = INPUT_STATE;
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
	tab_key(buffer, cursor, c);
	backspace_key(buffer, cursor, c);
	return_key(buffer, cursor, c);
	return (0);
}

int			read_input(t_shell *shell)
{
	char		c;
	int			ret;

	c = '\0';
	shell->buffer->buff_len = ft_strlen(shell->buffer->buff);
	ret = read(STDIN_FILENO, &c, 1);
	if (ret == -1)
		return (2);
	if (ret == 1)
	{
		ret = read_esc_seq(c, &shell->cursor, shell->buffer, shell->hist);
		if (ret != 0)
			return (ret);
		if (handle_control_char(shell->buffer, &shell->cursor, c) != 0)
			return (1);
	}
	return (0);
}

int			read_esc_seq(char c, t_cursor *cursor, t_buff *buffer,
							t_history *hist)
{
	char	seq[ESC_SEQ_SIZE];
	int		ret;

	ft_bzero(seq, ESC_SEQ_SIZE);
	if (c == ESCAPE)
	{
		ret = read(STDIN_FILENO, seq, ESC_SEQ_SIZE);
		if (ret == -1)
			return (2);
		if (cut_copy_paste(buffer, cursor, seq, 0) != 0)
			return (1);
		shift_right_key(buffer, cursor, seq);
		shift_left_key(buffer, cursor, seq);
		left_arrow_key(buffer, cursor, seq);
		if (up_arrow_key(buffer, cursor, hist, seq) != 0 ||
		down_arrow_key(buffer, cursor, hist, seq) != 0)
			return (1);
		right_arrow_key(buffer, cursor, seq);
		home_key(buffer, cursor, seq);
		end_key(buffer, cursor, seq);
	}
	return (0);
}
