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

size_t		get_new_job_id(t_shell *shell)
{
	t_job	*job;

	if (shell == NULL || shell->job_control == NULL)
		return (0);
	job = shell->job_control->job_list;
	if (job == NULL)
		return (1);
	while (job->next != NULL)
		job = job->next;
	return (job->id + 1);
}

void		add_process_to_list(t_job *job, t_process *process, t_status status)
{
	t_process *temp;

	if (job == NULL || process == NULL)
		return ;
	job->status = status;
	process->status = status;
	if (job->processes == NULL)
		job->processes = process;
	else
	{
		temp = job->processes;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = process;
	}
}

void		add_job_to_list(t_shell *shell, t_job *job)
{
	t_job	*temp;

	if (shell->job_control == NULL)
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
	ft_printf("[%i] %i %s\n", job->id, job->pgrp, job->command);
	shell->job_control->previous = shell->job_control->current;
	shell->job_control->current = job->id;
}
