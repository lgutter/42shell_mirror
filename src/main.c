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
#include "handle_input.h"

int			cetushell(void)
{
	t_shell		*shell;
	char		*input;

	shell = ft_memalloc(sizeof(t_shell));
	shell->buffer = ft_memalloc(sizeof(t_buff));
	shell->hist = (t_history *)ft_memalloc(sizeof(t_history));
	if (shell == NULL || shell->buffer == NULL)
		return (handle_error(malloc_error));
	configure_terminal(shell, 1);
	initialize_history(shell->hist);
	while (1)
	{
		input = prompt_shell(shell, PROMPT_NORMAL);
		if (input == NULL)
			return (free_shell(shell, 1));
		handle_input(shell, &input);
		add_remove_update_history(shell->hist, input);
		free(input);
		input = NULL;
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
