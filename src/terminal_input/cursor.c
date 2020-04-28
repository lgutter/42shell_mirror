/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cursor.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:35:25 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/02/10 16:45:21 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"

static void	cursor_next_line(t_cursor *cursor, size_t len, size_t prompt_len)
{
	if (cursor->max.x == 0)
		return ;
	if ((((len - 1 + prompt_len) / cursor->max.x) + cursor->start.y) >
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
			cursor->current.y++;
	}
}

void		set_cursor_pos(t_cursor *cursor, size_t buff_len, size_t prompt_len)
{
	cursor_next_line(cursor, buff_len, prompt_len);
	ft_memset(&cursor->cur_buff, '\0', CUR_BUFF_SIZE);
	if (cursor->current.x < prompt_len && cursor->current.y == cursor->start.y)
		cursor->current.x = prompt_len;
	if (cursor->current.x > (buff_len + prompt_len) &&
			cursor->current.y == cursor->start.y)
		cursor->current.x = buff_len + prompt_len;
	ft_snprintf(cursor->cur_buff, CUR_BUFF_SIZE, "%c[%d;%dH", ESCAPE \
				, cursor->current.y, cursor->current.x);
}

void		get_cursor_pos(t_cursor *cursor, size_t prompt_len)
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
		cursor->start.x = prompt_len + 4;
	}
	cursor->current.x = prompt_len;
	cursor->current.y = cursor->start.y;
}
