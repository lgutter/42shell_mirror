/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_job_status.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 15:57:25 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/22 15:57:25 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

static void	update_current_previous_job(t_job_cont *job_control, size_t id)
{
	t_job	*job;
	size_t	temp;

	job = job_control->job_list;
	temp = 0;
	if (id == job_control->current)
	{
		job_control->current = job_control->previous;
		while (job != NULL && job->id != job_control->previous)
		{
			temp = job->id;
			job = job->next;
		}
		job_control->previous = temp;
	}
	else if (id == job_control->previous)
	{
		while (job != NULL && job->id != job_control->current)
		{
			temp = job->id;
			job = job->next;
		}
		job_control->previous = temp;
	}
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
	if ((opts & job_update_update) != 0)
		status = get_job_status(job);
	else
		status = job->status;
	next = job->next;
	if ((opts & job_print_mask) != 0 ||
		((opts & job_update_process) != 0 && status != job->status))
	{
		job->status = status;
		print_job_status(job, job_control->current,
						job_control->previous, (opts & job_print_mask));
		if ((opts & job_print_pid_mask) == 0 && job->status == exited)
			remove_job_from_list(job_control, job->id);
	}
	else
		job->status = status;
	return (next);
}
