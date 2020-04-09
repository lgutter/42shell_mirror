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

static void		print_buffer(t_buff *buffer)
{
	if (buffer->rv_end > buffer->rv_start) 
	{	
		ft_printf("%.*s%s", buffer->rv_start, buffer->buff, RV_MODE);
		ft_printf("%.*s", buffer->rv_end - buffer->rv_start, 
		&buffer->buff[buffer->rv_start]);
		ft_printf("%s%s", RV_RESET, &buffer->buff[buffer->rv_end]);
	}
	else if (buffer->rv_end < buffer->rv_start)
	{
		ft_printf("%.*s%s",buffer->rv_end, buffer->buff, RV_MODE);
		ft_printf("%.*s", buffer->rv_start - buffer->rv_end, 
		&buffer->buff[buffer->rv_end]);
		ft_printf("%s%s", RV_RESET, &buffer->buff[buffer->rv_start]);
	}
	else
		ft_printf("%s", buffer->buff);
}

static void		clear_prompt(t_cursor *cursor)
{
	ft_printf("%c[%d;%dH", ESCAPE , cursor->start.y, 0);
	send_terminal("cd");
}

static void		refresh_prompt(t_buff *buffer, t_cursor *cursor)
{
	clear_prompt(cursor);
	ft_printf("%s", PROMPT_STR);
	print_buffer(buffer);
	ft_printf("%s",  cursor->cur_buff);
}


int			prompt_shell(t_shell *shell)
{
	while (42)
	{
		get_winsize(shell);
		set_cursor_pos(&shell->cursor, shell->buffer->len);
		refresh_prompt(shell->buffer, &shell->cursor);
		if (read_input(shell) == 1)
			return (1);
	}
	return (0);
}
