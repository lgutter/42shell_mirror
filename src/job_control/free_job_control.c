/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_job_control.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/13 17:08:18 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/13 17:08:18 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

t_job		*free_job(t_job *job)
{
	if (job != NULL)
	{
		free(job->command);
		job->command = NULL;
		job->foreground = false;
		job->id = 0;
		job->next = NULL;
		free_process_list(job->processes);
		job->processes = NULL;
		job->status = 0;
		free(job);
	}
	return (NULL);
}

t_process	*free_process(t_process *process)
{
	if (process != NULL)
	{
		free(process->command);
		process->command = NULL;
		process->next = NULL;
		process->pgrp = 0;
		process->status = 0;
		free(process);
	}
	return (NULL);
}

t_process	*free_process_list(t_process *start)
{
	t_process	*next;
	t_process	*current;

	current = start;
	while (current != NULL)
	{
		next = current->next;
		free_process(current);
		current = next;
	}
	return (NULL);
}

t_job		*free_job_list(t_job *start)
{
	t_job	*next;
	t_job	*current;

	current = start;
	while (current != NULL)
	{
		next = current->next;
		free_job(current);
		current = next;
	}
	return (NULL);
}

t_job_cont	*free_job_control(t_job_cont *job_control)
{
	if (job_control != NULL)
	{
		free_job_list(job_control->job_list);
		job_control->job_list = NULL;
		job_control->current = 0;
		job_control->previous = 0;
		free(job_control);
	}
	return (NULL);
}
