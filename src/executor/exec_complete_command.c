/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_complete_command.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 15:46:44 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/08 20:27:59 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "signal_handler.h"
#include "processing.h"
#include "job_control.h"

int		exec_complete_command(t_shell *shell, t_complete_cmd *comp_cmd)
{
	int		ret;
	t_env	*env;
	t_job	*job;

	job = init_job(get_new_job_id(shell), comp_cmd->cmd_string,
					(comp_cmd->seperator_op != background_op));
	env = NULL;
	if (shell != NULL)
		env = shell->env;
	ret = 0;
	while (comp_cmd != NULL && ret != exit_shell_code)
	{
		ret = word_processing(shell, comp_cmd);
		if ((g_signal_handler & SIGINT_BUFF) == SIGINT_BUFF)
			return (1);
		if (ret == 0)
			ret = exec_pipe_sequence(comp_cmd->pipe_sequence, shell, job);
		if (job->status != exited)
			add_job_to_list(shell, job);
		comp_cmd = comp_cmd->next;
		if (g_error_internal != 0)
			ft_setstatus(env, g_error_internal);
		g_error_internal = 0;
	}
	return (ret);
}
