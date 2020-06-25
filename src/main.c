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

static t_shell	*alloc_shell(int interactive)
{
	t_shell		*shell;

	shell = (t_shell *)ft_memalloc(sizeof(t_shell));
	if (shell == NULL)
		return (NULL);
	shell->hist = NULL;
	if (interactive == 1)
	{
		shell->hist = (t_history *)ft_memalloc(sizeof(t_history) * 1);
		if (shell->hist == NULL)
			handle_error_str(malloc_error, "when creating history");
	}
	shell->buffer = (t_buff *)ft_memalloc(sizeof(t_buff) * 1);
	if (shell->buffer == NULL)
	{
		free_shell(shell, 0);
		handle_error(malloc_error);
		shell = NULL;
	}
	return (shell);
}

static t_shell	*init_shell(int interactive)
{
	t_shell		*shell;
	char		*temp;

	shell = alloc_shell(interactive);
	if (shell == NULL)
		return (handle_error_p(malloc_error, NULL));
	shell->env = dup_sys_env();
	if (shell->env == NULL)
	{
		free_shell(shell, 0);
		return (handle_error_p(malloc_error, NULL));
	}
	temp = ft_getenv(shell->env, "HOME", VAR_TYPE);
	ft_setenv(shell->env, "HOME", temp, SHELL_VAR);
	free(temp);
	shell->interactive = interactive;
	if (interactive == 1)
	{
		configure_terminal(shell, 1);
	}
	if (shell->hist != NULL)
		initialize_history(shell);
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
	if (shell->interactive == 1)
		ft_printf("exit\n");
	free_shell(shell, 1);
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
		if ((g_signal_handler & SIGINT_BUFF) == SIGINT_BUFF)
		{
			free(input);
			input = shell->interactive == 1 ? ft_strdup("") : NULL;
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

int				main(void)
{
	t_shell		*shell;
	int			interactive;

	interactive = isatty(STDIN_FILENO);
	shell = init_shell(interactive);
	if (shell == NULL)
		return (1);
	else
		return (cetushell(shell));
}
