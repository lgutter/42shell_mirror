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

int		cetushell(char **env)
{
	char c;
	t_shell		*shell;

	shell = ft_memalloc(sizeof(t_shell));
	shell->envi = env;
	configure_terminal(shell, 1);
	while (read(STDIN_FILENO, &c, 1) == 1)
	{
		if (!ft_isprint(c))
			ft_printf("%d\n", c);
		else
			ft_printf("%d ('%c')\n", c, c);
		if (c == 'q')
			return (1);
	}
	configure_terminal(shell, 0);
	return (0);
}

int		main(int ac, char **av, char **env)
{
	if (ac != 1)
		ft_dprintf(2, " %s is not an argument?! No arguments needed!\n", av[1]);
	else
	{
		while (21)
			if (cetushell(env) == 1)
				return (0);
	}
	return (1);
}
