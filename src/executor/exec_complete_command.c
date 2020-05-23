/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_complete_command.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 15:46:44 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/23 16:43:09 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "signal_handler.h"

int		exec_complete_command(t_shell *shell, t_complete_cmd *comp_cmd)
{
	int		ret;
	t_env	*env;

	env = NULL;
	if (shell != NULL)
		env = shell->env;
	ret = 0;
	while (comp_cmd != NULL && ret != exit_shell_code)
	{
		ret = word_processing(shell, comp_cmd);
		if (g_signal_handler & SIGINT_BUFF)
			return (1);
		if (ret == 0)
			ret = exec_pipe_sequence(comp_cmd->pipe_sequence, env);
		comp_cmd = comp_cmd->next;
		if (g_error_internal != 0)
			ft_setstatus(env, g_error_internal);
		g_error_internal = 0;
	}
	return (ret);
}
