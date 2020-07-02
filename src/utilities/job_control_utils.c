/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   job_control_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 12:03:36 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/08 17:41:16 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

t_job		*init_job(size_t id, char *command, bool foreground)
{
	t_job	*job;

	job = (t_job *)ft_memalloc(sizeof(t_job) * 1);
	if (job != NULL)
	{
		job->id = id;
		job->pgrp = 0;
		job->status = running;
		job->foreground = foreground;
		job->command = ft_strdup(command);
		job->processes = NULL;
		job->next = NULL;
	}
	return (job);
}

t_process	*init_process(pid_t *pgrp, char *command)
{
	t_process	*process;

	process = (t_process *)ft_memalloc(sizeof(t_process) * 1);
	if (process != NULL)
	{
		process->pid = 0;
		process->pgrp = pgrp;
		process->status = running;
		process->command = ft_strdup(command);
		process->next = NULL;
	}
	return (process);
}

int			set_process_job_group(t_job *job, t_process *process)
{
	if (job == NULL || process == NULL)
		return (-1);
	if (job->pgrp == 0)
		job->pgrp = process->pid;
	setpgid (process->pid, job->pgrp);
	return (0);
}
