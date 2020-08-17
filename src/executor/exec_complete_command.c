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
#include "hashtable.h"

static t_complete_cmd	*skip_and_or_list(t_shell *shell, t_complete_cmd *cmd)
{
	if (cmd->seperator_op == and_op)
	{
		if (ft_getstatus(shell->env) != 0 && cmd->next != NULL)
			return (cmd->next);
	}
	if (cmd->seperator_op == or_op)
	{
		if (ft_getstatus(shell->env) == 0 && cmd->next != NULL)
			return (cmd->next);
	}
	return (cmd);
}

static int				handle_command(t_shell *shell, t_complete_cmd *comp_cmd)
{
	t_job	*job;
	int		ret;

	job = init_job(shell, comp_cmd->cmd_string,
				(comp_cmd->seperator_op != background_op));
	if (job == NULL)
		return (malloc_error);
	ret = word_processing(shell, comp_cmd);
	if (ret == 0)
		ret = exec_pipe_sequence(comp_cmd->pipe_sequence, shell, job);
	job->status = get_job_status(job);
	if (job->status != exited && job->status != broken_pipe)
		add_job_to_list(shell, job);
	else
		free_job(job);
	return (ret);
}

int						exec_complete_command(t_shell *shell,
													t_complete_cmd *comp_cmd)
{
	int		ret;

	ret = 0;
	if (shell == NULL)
		return (handle_error_str(internal_error, "shell struct is NULL"));
	while (comp_cmd != NULL && ret != exit_shell_code)
	{
		if ((g_signal_handler & (1 << SIGINT)) != 0)
			return (1);
		ret = handle_command(shell, comp_cmd);
		comp_cmd = skip_and_or_list(shell, comp_cmd);
		comp_cmd = comp_cmd->next;
	}
	return (ret);
}
