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

void		set_cursor_pos(t_cursor *cursor, size_t len)
{
	ft_memset(&cursor->cur_buff, 0, 32);
	if (cursor->x < PROMPT_LEN)
		cursor->x = PROMPT_LEN;
	if (cursor->x > (len + PROMPT_LEN))
		cursor->x = len + PROMPT_LEN;
	ft_snprintf(cursor->cur_buff, 16, "%c[%d;%dH", 27 , cursor->y, cursor->x);
}

void		get_cursor_pos(t_cursor *cursor, int init)
{
	char	pos[16];
	int		ret;

	ret = 0;
	ft_memset(&pos, '\0', sizeof(pos));
	send_terminal("u7");
	ret = read(STDIN_FILENO, &pos, sizeof(pos) - 1);
	cursor->y = ft_atoi(&pos[2]);
	while (!ft_isdigit(pos[ret]))
		ret = ret - 1;
	while (ft_isdigit(pos[ret - 1]))
		ret = ret - 1;
	cursor->x = ft_atoi(&pos[ret]);
	if (init == 1)
		cursor->x = PROMPT_LEN;
	ft_printf("(%d,%d)", cursor->y, cursor->x);
}

void		send_terminal_cursor(size_t	hpos, size_t vpos)
{
	tgoto(tgetstr("", NULL), hpos, vpos);
}
