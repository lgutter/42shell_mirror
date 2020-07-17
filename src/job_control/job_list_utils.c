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
	print_job_status(job, shell->job_control->current,
						shell->job_control->previous, job_print_pids);
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
			status = process->status;
		process = process->next;
	}
	return (status);
}

static void	update_current_previous_job(t_job_cont *job_control, size_t id)
{
	if (id == job_control->current)
	{
		job_control->current = job_control->previous;
		job_control->previous = get_new_job_id(job_control);
		if (job_control->previous > 0)
			job_control->previous -= 1;
	}
	if (id == job_control->previous)
	{
		job_control->previous = get_new_job_id(job_control);
		if (job_control->previous > 0)
			job_control->previous -= 1;
	}
	if (job_control->previous == job_control->current)
		job_control->previous = 0;
}

static void	remove_job_from_list(t_job_cont *job_control, size_t id)
{
	t_job	*current;
	t_job	*prev;
	t_job	*next;

	current = job_control->job_list;
	prev = NULL;
	while (current != NULL)
	{
		if (current->id == id)
		{
			next = current->next;
			current = free_job(current);
			if (prev == NULL)
				job_control->job_list = next;
			else
				prev->next = next;
			break ;
		}
		prev = current;
		current = current->next;
	}
	update_current_previous_job(job_control, id);
}

t_job		*update_job_status(t_job_cont *job_control, t_job *job, int opts)
{
	t_status	status;
	t_job		*next;

	if (job_control == NULL || job == NULL)
		return (NULL);
	status = get_job_status(job);
	if ((opts & job_update_print) != 0 && status != job->status)
	{
		job->status = status;
		print_job_status(job, job_control->current,
						job_control->previous, job_print_auto);
	}
	job->status = status;
	next = job->next;
	if ((opts & job_update_remove) != 0 && status == exited)
		remove_job_from_list(job_control, job->id);
	return (next);
}
