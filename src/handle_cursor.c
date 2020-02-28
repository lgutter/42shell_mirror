/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_cursor.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: Invalid date        by                #+#    #+#                */
/*   Updated: 0003/01/01 00:00:00 by               ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "configure_terminal.h"

void		set_cursor_pos(t_cursor *cursor, size_t len)
{

	ft_memset(&cursor->cur_buff, 0, 32);
	if (cursor->x < PROMPT_LEN && cursor->layer == 0)
		cursor->x = PROMPT_LEN;
	if (cursor->x > (len + PROMPT_LEN))
		cursor->x = len + PROMPT_LEN;
	ft_printf("\nx == %d\n", cursor->x);
	ft_snprintf(cursor->cur_buff, 16, "%c[%d;%dH", 27 , cursor->y, cursor->x);
}

void		cursor_next_line(t_shell *shell)
{
	//ft_printf("\ntest: (%d)\n", shell->cursor.x_max);
	if (shell->cursor.x > shell->cursor.x_max)
	{
		//shell->buffer.buff[shell->cursor.x] = '\n';
		shell->cursor.x = 0;
		shell->cursor.y = shell->cursor.y + 1;
		shell->cursor.layer = shell->cursor.layer + 1;
	}
}

void		cursor_pos(t_shell *shell)
{
	get_winsize(shell);
	shell->cursor.x_max = shell->winsize.ws_col - 2;
	shell->cursor.y_max = shell->winsize.ws_row;
	cursor_next_line(shell);
	set_cursor_pos(&shell->cursor, shell->buffer.len);
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
