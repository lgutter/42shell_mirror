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

static void		cursor_next_line(t_cursor *cursor)
{
	if (cursor->current.x > cursor->max.x)
	{
		cursor->current.x = 1;
		if (cursor->current.y != cursor->max.y)
			cursor->current.y++;
		else
		{
			cursor->start.y--;
			send_terminal(CURSOR_DOWN);
		}
	}
	if (cursor->current.x <= 0)
	{
		cursor->current.x = cursor->max.x;
		if (cursor->current.y != cursor->start.y)
			cursor->current.y--;
	}
}

void		set_cursor_pos(t_cursor *cursor, size_t len)
{
	cursor_next_line(cursor);
	ft_memset(&cursor->cur_buff, 0, 32);
	if (cursor->current.x < PROMPT_LEN && cursor->current.y == cursor->start.y)
		cursor->current.x = PROMPT_LEN;
	if (cursor->current.x > (ssize_t)(len + PROMPT_LEN) &&
			cursor->current.y == cursor->start.y)
		cursor->current.x = len + PROMPT_LEN;
	ft_snprintf(cursor->cur_buff, CUR_BUFF_SIZE, "%c[%d;%dH", ESCAPE \
				, cursor->current.y, cursor->current.x);
}

void		get_cursor_pos(t_cursor *cursor)
{
	char	pos[16];
	int		ret;

	ret = 0;
	ft_memset(&pos, '\0', sizeof(pos));
	send_terminal(CURSOR_POSITION);
	ret = read(STDIN_FILENO, &pos, sizeof(pos) - 1);
	cursor->start.y = ft_atoi(&pos[2]);
	while (!ft_isdigit(pos[ret]))
		ret = ret - 1;
	while (ft_isdigit(pos[ret - 1]))
		ret = ret - 1;
	cursor->start.x = ft_atoi(&pos[ret]);
	cursor->current.x = PROMPT_LEN;
	cursor->current.y = cursor->start.y;
}
