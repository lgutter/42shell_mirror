/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 11:39:06 by dkroeke        #+#    #+#                */
/*   Updated: 2020/02/12 11:39:06 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void		send_terminal_cursor(size_t	hpos, size_t vpos)
{
	tgoto(tgetstr("", NULL), hpos, vpos);
}

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

int			cetushell(char **env)
{
	char c;
	t_shell		*shell;
	ssize_t		ret;

	shell = ft_memalloc(sizeof(t_shell));
	shell->envi = env;
	configure_terminal(shell, 1);
	get_cursor_pos(&shell->cursor);
	shell->buffer.len = 0;
	ft_bzero(&shell->buffer.buff, 2048);
	ft_printf("\nCetush >>");
	while (1)
	{
		get_winsize(shell);
		c = '\0';
		ret = read(STDIN_FILENO, &c, 1);
		if (ret == -1)
			ft_dprintf(2, "ERROR");
		if (ret == 1)
		{
			send_terminal("cb");
			send_terminal("up");
			//send_terminal("vs");
			ft_printf("\nCetush >>");
			//send_terminal("rc");

			if (ft_isprint(c))
			{
				ft_printf("%s", shell->buffer.buff);
				shell->buffer.buff[shell->buffer.len] = c;
				shell->buffer.len = shell->buffer.len + 1;
			}
		}
		if (c == 10)
		{
			shell->buffer.len = 0;
			ft_printf("\nCetush >>");
			//send_terminal_cursor(0, 0);q
		}
		if (c == 'q')
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
