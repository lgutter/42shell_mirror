/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 13:17:06 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/08 17:37:34 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "handle_error.h"
#include "history.h"
#include "environment.h"
#include "utils.h"
#include "prompt.h"
#include "signal_handler.h"
#include "job_control.h"

static t_shell	*alloc_shell(bool interactive)
{
	t_shell		*shell;

	shell = (t_shell *)ft_memalloc(sizeof(t_shell));
	if (shell == NULL)
		return (NULL);
	shell->hist = NULL;
	shell->job_control = NULL;
	if (interactive == true)
	{
		shell->hist = (t_history *)ft_memalloc(sizeof(t_history) * 1);
		if (shell->hist == NULL)
			handle_error_str(malloc_error, "when creating history");
		shell->job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont) * 1);
		if (shell->job_control == NULL)
			handle_error_str(malloc_error, "when creating job control");
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

t_shell			*init_shell(bool interactive)
{
	t_shell		*shell;
	char		*temp;

	if (interactive == true)
		setup_signals();
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
	configure_terminal(shell, interactive == 1 ? 2 : 1);
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
		free_job_control(shell->job_control);
		shell->job_control = NULL;
		configure_terminal(NULL, 0);
		free_env_list(shell->env);
		free(shell);
	}
	return (ret);
}
