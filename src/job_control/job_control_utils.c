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
#include "environment.h"
#include <signal.h>
#include <sys/wait.h>

t_status		get_status_from_stat_loc(int stat_loc, t_process *process)
{
	if (process == NULL)
		return (exited);
	if (WIFSTOPPED(stat_loc) == true)
		process->status = suspended;
	else if (WIFSIGNALED(stat_loc) == true)
	{
		process->signal = WTERMSIG(stat_loc);
		if (process->signal == SIGPIPE)
			process->status = broken_pipe;
		else
			process->status = exited;
	}
	else if (WIFCONTINUED(stat_loc) == true)
		process->status = running;
	else
		process->status = exited;
	return (process->status);
}

int				handle_new_process(t_shell *shell, t_job *job,
															t_process *process)
{
	int	stat_loc;
	int	ret;

	if (shell == NULL || job == NULL || process == NULL)
		return (-1);
	ret = 0;
	if (job->foreground == true)
	{
		process->status = exited;
		ret = waitpid(process->pid, &stat_loc, WUNTRACED | WCONTINUED);
		if (ret > 0)
		{
			process->status = get_status_from_stat_loc(stat_loc, process);
			if (WIFEXITED(stat_loc) != 0)
				ret = (int)WEXITSTATUS(stat_loc);
			else
				ret = 0;
		}
	}
	else
		process->status = running;
	return (ret);
}

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

int				set_process_job_group(t_job *job, t_process *process)
{
	if (job == NULL || process == NULL)
		return (-1);
	if (job->pgrp == 0)
		job->pgrp = process->pid;
	setpgid(process->pid, job->pgrp);
	return (0);
}
