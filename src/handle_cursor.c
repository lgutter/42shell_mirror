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

void		get_cursor_pos(t_cursor *cursor)
{
	char	pos[16];
	int		ret;

	ret = 0;
	ft_memset(&pos, '\0', sizeof(pos));
	send_terminal("u7");
	ret = read(STDIN_FILENO, &pos, sizeof(pos) - 1);
	cursor->x = ft_atoi(&pos[2]);
	while (!ft_isdigit(pos[ret]))
		ret = ret - 1;
	while (ft_isdigit(pos[ret - 1]))
		ret = ret - 1;
	cursor->y = ft_atoi(&pos[ret]);
}

void		send_terminal_cursor(size_t	hpos, size_t vpos)
{
	tgoto(tgetstr("", NULL), hpos, vpos);
}
