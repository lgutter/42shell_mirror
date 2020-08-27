/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_job_control.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/26 10:45:21 by lgutter       #+#    #+#                 */
/*   Updated: 2020/08/26 10:45:21 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

t_job			*init_job(t_shell *shell, char *command, bool foreground)
{
	t_job	*job;
	size_t	id;

	id = 0;
	if (shell != NULL)
		id = get_new_job_id(shell->job_control);
	job = (t_job *)ft_memalloc(sizeof(t_job) * 1);
	if (job != NULL)
	{
		job->id = id;
		job->pgrp = 0;
		job->status = exited;
		job->foreground = foreground;
		job->command = ft_strdup(command);
		job->processes = NULL;
		job->next = NULL;
	}
	return (job);
}

t_process		*init_process(t_job *job, char *command)
{
	t_process	*process;
	t_process	*temp;

	if (job == NULL)
		return (NULL);
	process = (t_process *)ft_memalloc(sizeof(t_process) * 1);
	if (process != NULL)
	{
		process->pid = 0;
		process->pgrp = &(job->pgrp);
		process->status = exited;
		process->command = ft_strdup(command);
		process->next = NULL;
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
	return (process);
}
