/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:52:43 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/04/14 11:52:43 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"
#include "prompt_str.h"

int			cetushell(void)
{
	t_shell		*shell;
	char		*input;

	shell = ft_memalloc(sizeof(t_shell));
	if (shell == NULL)
		return (1);
	configure_terminal(shell, 1);
	while (1)
	{
		input = prompt_shell(shell, g_prompt[NORMAL]);
		if (input == NULL)
		{
			configure_terminal(shell, 0);
			return (1);
		}
	}
	return (0);
}

int			main(int ac, char **av)
{
	if (ac != 1)
		ft_dprintf(2, "Huh? why %s? No arguments needed!\n", av[1]);
	else
	{
		while (21)
			if (cetushell() == 1)
				return (0);
	}
	return (1);
}
