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

int			cetushell(char **env)
{
	t_shell		*shell;

	shell = ft_memalloc(sizeof(t_shell));
	shell->buffer = ft_memalloc(sizeof(t_buff));
	if (shell->buffer == NULL || shell == NULL)
		return (1);
	shell->envi = env;
	configure_terminal(shell, 1);
	while (1)
	{
		if (init_buffs(shell->buffer, &shell->cursor) == 1)
			return (1);
		if (prompt_shell(shell) == 1)
		{
			configure_terminal(shell, 0);
			return (1);
		}
	}
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
