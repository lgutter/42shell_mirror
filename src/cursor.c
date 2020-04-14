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

static void		cursor_next_line(t_cursor *cursor, size_t len)
{
	if ((((len - 1 + PROMPT_LEN) / cursor->max.x) + cursor->start.y) >
	cursor->max.y)
	{
		send_terminal(CURSOR_DOWN);
		cursor->start.y--;
		cursor->current.y--;
	}
	if (cursor->current.x > cursor->max.x)
	{
		cursor->current.x = 1;
		if (cursor->current.y != cursor->max.y)
			cursor->current.y++;
	}
	if (cursor->current.x == 0)
	{
		cursor->current.x = cursor->max.x;
		if (cursor->current.y != cursor->start.y)
			cursor->current.y--;
	}
}

void		set_cursor_pos(t_cursor *cursor, size_t len)
{
	cursor_next_line(cursor, len);
	ft_memset(&cursor->cur_buff, '\0', CUR_BUFF_SIZE);
	if (cursor->current.x < PROMPT_LEN && cursor->current.y == cursor->start.y)
		cursor->current.x = PROMPT_LEN;
	if (cursor->current.x > (len + PROMPT_LEN) &&
			cursor->current.y == cursor->start.y)
		cursor->current.x = len + PROMPT_LEN;
	ft_snprintf(cursor->cur_buff, CUR_BUFF_SIZE, "%c[%d;%dH", ESCAPE \
				, cursor->current.y, cursor->current.x);
}

void		get_cursor_pos(t_cursor *cursor)
{
	char	pos[16];
	int		ret;
	int		temp;

	send_terminal(CURSOR_POSITION);
	ft_memset(&pos, '\0', sizeof(pos));
	ret = read(STDIN_FILENO, &pos, sizeof(pos));
	if (ret == -1)
		return ;
	if (ret < 3)
		read(STDIN_FILENO, &pos, sizeof(pos));
	else
	{
		temp = ft_atoi(&pos[2]);
		if (temp != 0)
			cursor->start.y = temp;
		while (ft_isdigit(pos[ret]) == 0)
			ret = ret - 1;
		while (ft_isdigit(pos[ret - 1]) == 1)
			ret = ret - 1;
		cursor->start.x = ft_atoi(&pos[ret]);
	}
	cursor->current.x = PROMPT_LEN;
	cursor->current.y = cursor->start.y;
}
