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
#include "controls_shell.h"
#include "configure_terminal.h"

int			handle_input(t_buff *buffer, t_cursor *cursor)
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
		handle_esc_seq(c, cursor);
		if (ft_isprint(c))
		{
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
			ft_memset(&buffer->buff, '\0', buffer->len);
			buffer->len = 0;
			cursor->x = 10;
			send_terminal("do");
		}
		handle_tab(c, buffer, cursor);
		handle_backspace(c, buffer, cursor);
		set_cursor_pos(cursor);
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

}

int			prompt_shell(t_shell *shell)
{
	while (42)
	{
		send_terminal("cb");
		send_terminal("up");
		ft_printf("\nCetush >>%s", shell->buffer.buff);
		ft_printf("%s", shell->cursor.cur_buff);
		if (handle_input(&shell->buffer, &shell->cursor) == 1)
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
<<<<<<< HEAD
	get_cursor_pos(&shell->cursor);
=======
	init_buffs(shell);
>>>>>>> 94f42877c650e6d3b196e6ba0808effffb5ce1e8
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
