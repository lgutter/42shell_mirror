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

static size_t	get_new_job_id(t_shell *shell)
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

t_job			*init_job(t_shell *shell, char *command, bool foreground)
{
	t_job	*job;
	size_t	id;

	id = get_new_job_id(shell);
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

int				set_process_job_group(t_job *job, t_process *process)
{
	if (job == NULL || process == NULL)
		return (-1);
	if (job->pgrp == 0)
		job->pgrp = process->pid;
	setpgid(process->pid, job->pgrp);
	return (0);
}

void			print_job_status(t_job *job, size_t current, size_t prev)
{
	t_process	*process;
	char		curprev;
	const char	*statuses[3] = {
		"running",
		"suspended",
		"exited"
	};

	if (job == NULL)
		return ;
	process = job->processes;
	if (job->id == current)
		curprev = '+';
	else if (job->id == prev)
		curprev = '-';
	else
		curprev = ' ';
	if (process != NULL)
		ft_printf("[%i] %c\n", job->id, curprev);
	while (process != NULL)
	{
		ft_printf("\t%5lu %-10s %s\n",
				process->pid, statuses[process->status], process->command);
		process = process->next;
	}
}
