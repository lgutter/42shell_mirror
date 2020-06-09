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
#include "prompt.h"
#include "handle_input.h"
#include "history.h"
#include "signal_handler.h"

static t_shell	*init_shell(void)
{
	t_shell		*shell;
	char		*temp;

	shell = (t_shell *)ft_memalloc(sizeof(t_shell));
	if (shell == NULL)
		return (handle_error_p(malloc_error, NULL));
	shell->buffer = (t_buff *)ft_memalloc(sizeof(t_buff) * 1);
	shell->hist = (t_history *)ft_memalloc(sizeof(t_history) * 1);
	shell->env = dup_sys_env();
	temp = ft_getenv(shell->env, "HOME", VAR_TYPE);
	ft_setenv(shell->env, "HOME", temp, SHELL_VAR);
	free(temp);
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

static int		exit_shell(t_shell *shell, int ret)
{
	char	*exit_code;

	exit_code = ft_getenv(shell->env, "EXIT_CODE", SHELL_VAR);
	if (exit_code == NULL)
		exit_code = ft_getenv(shell->env, "STATUS", SHELL_VAR);
	if (exit_code != NULL)
		ret = ft_atoi(exit_code);
	free(exit_code);
	free_shell(shell, 1);
	ft_printf("exit\n");
	return (ret);
}

static int		cetushell(t_shell *shell)
{
	char		*input;
	char		*prompt;
	int			ret;

	ret = 0;
	while (ret != exit_shell_code)
	{
		prompt = ft_getenv(shell->env, "PS1", SHELL_VAR);
		input = prompt_shell(shell, prompt == NULL ? PROMPT_NORMAL : prompt);
		free(prompt);
		if (g_signal_handler == SIGINT_BUFF)
		{
			free(input);
			input = ft_strdup("");
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
	t_shell		*shell;

	if (write(STDIN_FILENO, "\0", 0) == -1)
		return (1);
	shell = init_shell();
	if (shell == NULL)
	{
		return (1);
	}
	else
	{
		return (cetushell(shell));
	}
}
