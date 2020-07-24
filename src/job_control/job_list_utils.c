/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   job_list_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/10 14:19:21 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/10 14:19:21 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

size_t		get_new_job_id(t_job_cont *job_control)
{
	t_job	*job;

	if (job_control == NULL)
		return (0);
	job = job_control->job_list;
	if (job == NULL)
		return (1);
	while (job->next != NULL)
		job = job->next;
	return (job->id + 1);
}

void		add_job_to_list(t_shell *shell, t_job *job)
{
	t_job	*temp;

	if (shell == NULL || shell->job_control == NULL)
		return ;
	if (shell->job_control->job_list == NULL)
		shell->job_control->job_list = job;
	else
	{
		temp = shell->job_control->job_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = job;
	}
	shell->job_control->previous = shell->job_control->current;
	shell->job_control->current = job->id;
	if (job->status == running)
		print_job_status(job, shell->job_control->current,
						shell->job_control->previous, job_print_pids);
	else
		print_job_status(job, shell->job_control->current,
						shell->job_control->previous, job_print_auto);
}

t_status	get_job_status(t_job *job)
{
	t_process	*process;
	t_status	status;

	if (job == NULL || job->processes == NULL)
		return (exited);
	process = job->processes;
	status = process->status;
	while (process != NULL)
	{
		if (process->status == running)
			return (running);
		if (process->status == suspended)
			status = suspended;
		if (status == broken_pipe && process->status == exited)
			status = exited;
		process = process->next;
	}
	return (status);
}
