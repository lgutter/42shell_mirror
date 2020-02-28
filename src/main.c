/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: Invalid date        by                #+#    #+#                */
/*   Updated: 0003/01/01 00:00:00 by               ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "controls_shell.h"
#include "configure_terminal.h"

int			handle_control_char(t_buff *buffer, t_cursor *cursor, char c)
{
	if (ft_isprint(c))
	{
		if (c == 'p')
		{
			buffer->buff[buffer->len] = '\n';
			cursor->x = cursor->x + 1;
			buffer->len = buffer->len + 1;
		}
		if (c == 'q')
			return (1);
		if (insert_char(buffer, cursor, c) == 0)
		{
			buffer->buff[buffer->len] = c;
			cursor->x = cursor->x + 1;
			buffer->len = buffer->len + 1;
		}
	}
	if (c == 10)
	{
		cursor->y++;
		ft_printf("\noutput: %s", buffer->buff);
		ft_memset(&buffer->buff, '\0', buffer->len);
		buffer->len = 0;
		cursor->x = PROMPT_LEN;
		send_terminal("do");
	}
	handle_tab(c, buffer, cursor);
	handle_backspace(c, buffer, cursor);
	return (0);
}

int			read_input(t_shell *shell)
{
	char		c;
	ssize_t		ret;

	c = '\0';
	ret = read(STDIN_FILENO, &c, 1);
	if (ret == -1)
		ft_dprintf(2, "ERROR");
	if (ret == 1)
	{
		//ft_printf("\n(%d)\n", c);
		handle_esc_seq(c, &shell->cursor);
		if (handle_control_char(&shell->buffer, &shell->cursor, c) == 1)
			return (1);
		cursor_pos(shell);
	}
	return (0);
}

void		init_buffs(t_shell *shell)
{
	get_winsize(shell);
	shell->buffer.len = 0;
	ft_memset(&shell->buffer.buff, '\0', 2048);
	ft_memset(&shell->cursor.cur_buff, 0, 32);
	get_cursor_pos(&shell->cursor, 1);
	shell->cursor.layer = 0;
}

void		refresh_prompt(t_buff buffer, t_cursor cursor)
{
	size_t		i;

	i = 0;
	while (i <= cursor.layer)
	{
		send_terminal("cb");
		send_terminal("up");
		i++;
	}
	ft_printf("\nCetush >>%s", buffer.buff);
	ft_printf("%s", cursor.cur_buff);
}

int			prompt_shell(t_shell *shell)
{
	while (42)
	{
		refresh_prompt(shell->buffer, shell->cursor);
		if (read_input(shell) == 1)
			return (1);
	}
	return (0);
}

int			cetushell(char **env)
{
	t_shell		*shell;

	shell = ft_memalloc(sizeof(t_shell));
	shell->envi = env;
	configure_terminal(shell, 1);
	init_buffs(shell);
	while (1)
	{
		if (prompt_shell(shell) == 1)
			return (1);
	}
	configure_terminal(shell, 0);
	return (0);
}

int		main(int ac, char **av, char **env)
{
	if (ac != 1)
		ft_dprintf(2, "Huh? why %s? No arguments needed!\n", av[1]);
	else
	{
		while (21)
			if (cetushell(env) == 1)
				return (0);
	}
	return (1);
}
