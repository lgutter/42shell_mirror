/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:52:43 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/05/23 16:21:37 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"
#include "handle_input.h"
#include "history.h"
#include "signal_handler.h"

static t_shell	*init_shell(void)
{
	t_shell		*shell;

	shell = (t_shell *)ft_memalloc(sizeof(t_shell));
	if (shell == NULL)
		return (handle_error_p(malloc_error, NULL));
	shell->buffer = (t_buff *)ft_memalloc(sizeof(t_buff));
	shell->hist = (t_history *)ft_memalloc(sizeof(t_history));
	shell->env = dup_sys_env();
	ft_setenv(shell->env, "HOME", getenv("HOME"), SHELL_VAR);
	configure_terminal(shell, 1);
	if (shell->hist == NULL)
		handle_error(malloc_error);
	else
		initialize_history(shell);
	if (shell->buffer == NULL || shell->env == NULL)
	{
		free_shell(shell, 0);
		if (shell->buffer == NULL)
			handle_error(malloc_error);
		shell = NULL;
	}
	return (shell);
}

int				exit_shell(t_shell *shell, int ret)
{
	char	*exit_code;

	exit_code = ft_getenv(shell->env, "EXIT_CODE", SHELL_VAR);
	if (exit_code != NULL)
		ret = ft_atoi(exit_code);
	free(exit_code);
	free_shell(shell, 1);
	printf("exit\n");
	return (ret);
}

int				cetushell(void)
{
	t_shell		*shell;
	char		*input;
	int			ret;

	ret = 0;
	shell = init_shell();
	if (shell == NULL)
		return (1);
	while (ret != exit_shell_code)
	{
		input = prompt_shell(shell, PROMPT_NORMAL);
		if (g_signal_handler == SIGINT_BUFF)
		{
			free(input);
			input = strdup("");
		}
		if (input == NULL)
			break ;
		ret = handle_input(shell, &input);
		update_history(shell->hist, shell->env, input);
		free(input);
		input = NULL;
		g_signal_handler = 0;
	}
	return (exit_shell(shell, ret));
}

int				main(int ac, char **av)
{
	if (ac != 1)
		ft_dprintf(2, "Huh? why %s? No arguments needed!\n", av[1]);
	else
	{
		return (cetushell());
	}
	return (1);
}
