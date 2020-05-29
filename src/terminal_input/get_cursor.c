/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_cursor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/29 19:44:43 by devan         #+#    #+#                 */
/*   Updated: 2020/05/29 19:44:43 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"

static void	parse_cursor_pos(t_cursor *cursor, char *pos, size_t prompt_len
							, int ret)
{
	int		temp;

	temp = ft_atoi(&pos[2]);
	if (temp != 0)
		cursor->start.y = temp;
	while (ft_isdigit(pos[ret]) == 0)
		ret = ret - 1;
	while (ft_isdigit(pos[ret - 1]) == 1)
		ret = ret - 1;
	cursor->current.x = ft_atoi(&pos[ret]);
	if (cursor->current.x > 1)
	{
		cursor->start.y++;
		cursor->new_line_x = cursor->current.x;
	}
	else
		cursor->start.x = prompt_len;
}

void		get_cursor_pos(t_cursor *cursor, size_t prompt_len)
{
	char	pos[16];
	int		ret;

	if (cursor == NULL)
		return ;
	send_terminal("sc");
	ft_printf("%c[6n", ESCAPE_KEY);
	ft_memset(&pos, '\0', sizeof(pos));
	ret = read(STDIN_FILENO, &pos, sizeof(pos));
	if (ret == -1)
		return ;
	if (ret < 3)
		read(STDIN_FILENO, &pos, sizeof(pos));
	else
		parse_cursor_pos(cursor, pos, prompt_len, ret);
	cursor->current.x = prompt_len;
	cursor->current.y = cursor->start.y;
}
