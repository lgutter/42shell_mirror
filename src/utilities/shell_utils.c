/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 13:17:06 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/02 13:17:06 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "handle_error.h"
#include "history.h"
#include "environment.h"
#include "utils.h"
#include "prompt.h"

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

t_shell			*init_shell(int interactive)
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

int				free_shell(t_shell *shell, int ret)
{
	if (shell != NULL)
	{
		free_history(shell->hist);
		shell->hist = NULL;
		free_buffer_buffs(shell, 1);
		if (shell->buffer != NULL)
			free(shell->buffer);
		shell->buffer = NULL;
		configure_terminal(shell, 0);
		free_env_list(shell->env);
		free(shell);
	}
	return (ret);
}
