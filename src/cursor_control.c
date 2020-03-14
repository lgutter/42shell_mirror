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
#include "configure_terminal.h"

/** the cursor will be tracked on its position and look if the cursor is on
 * the right layer. if at the beginning or the end it will change the layer (y-cursor).
 */
void		cursor_next_line(t_cursor *cursor)
{
	if (cursor->current.x > cursor->max.x)
	{
		cursor->current.x = 1;
		if (cursor->current.y != cursor->max.y)
			cursor->current.y++;
		else
		{
			cursor->start.y--;
			send_terminal("do");
		}
	}
	if (cursor->current.x <= 0)
	{
		cursor->current.x = cursor->max.x;
		if (cursor->current.y != cursor->start.y)
			cursor->current.y--;
	}
}

/**
 * this function will actually set the cursor position which is set within the
 * cursor struct. it also makes sure that the cursor will not run off the screen
 * or in front of the prompt.
 */
void		cursor_pos(t_cursor *cursor, int len)
{
	cursor_next_line(cursor);
	ft_memset(&cursor->cur_buff, 0, 32);
	if (cursor->current.x < PROMPT_LEN && cursor->current.y == cursor->start.y)
		cursor->current.x = PROMPT_LEN;
	if (cursor->x > (ssize_t)(len + PROMPT_LEN) && cursor->current.y == cursor->start.y)
		cursor->current.x = len + PROMPT_LEN;
	ft_snprintf(cursor->cur_buff, 16, "%c[%d;%dH", 27 , cursor->current.y, cursor->current.x);
}

/**
 * Here the cursor position is extracted from the terminal by sending a
 * a termcap code(u7) which will give a string in return. Reading and Parsing
 * this string will give the x and y psoitions of the cursor. 
 */
void		get_cursor_pos(t_cursor *cursor, int init)
{
	char	pos[16];
	int		ret;

	ret = 0;
	ft_memset(&pos, '\0', sizeof(pos));
	send_terminal("u7");
	ret = read(STDIN_FILENO, &pos, sizeof(pos) - 1);
	cursor->start.y = ft_atoi(&pos[2]);
	while (!ft_isdigit(pos[ret]))
		ret = ret - 1;
	while (ft_isdigit(pos[ret - 1]))
		ret = ret - 1;
	cursor->start.x = ft_atoi(&pos[ret]);
	cursor->current.x = PROMPT_LEN;
	cursor->current.y = cursor->start.y;
	init++;
}
