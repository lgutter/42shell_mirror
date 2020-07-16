/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_jobs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 12:42:56 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/14 12:42:56 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include <sys/wait.h>
#include <sys/types.h>

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
	if (id == job_control->current)
		job_control->current = job_control->previous;
	if (job_control->current == 0 && prev != NULL)
		job_control->current = prev->id;
}

static int	update_process_status(t_job *start, pid_t pid, t_status status)
{
	t_process	*process;
	t_job		*job;

	job = start;
	while (job != NULL)
	{
		process = job->processes;
		while (process != NULL)
		{
			if (pid == process->pid)
			{
				process->status = status;
				return (0);
			}
			process = process->next;
		}
		job = job->next;
	}
	return (1);
}

static void	update_jobs(t_job_cont *job_control)
{
	t_job		*job;
	t_status	status;
	size_t		id;

	job = job_control->job_list;
	while (job != NULL)
	{
		status = get_job_status(job);
		if (status != job->status)
			print_job_status(job, job_control->current, job_control->previous);
		job->status = status;
		id = job->id;
		job = job->next;
		if (status == exited)
			remove_job_from_list(job_control, id);
	}
}

void		check_jobs(t_job_cont *job_control)
{
	int	stat_loc;
	int	ret;

	stat_loc = 0;
	ret = 1;
	if (job_control == NULL)
		return ;
	while (ret > 0)
	{
		ret = waitpid(-1, &stat_loc, WNOHANG | WUNTRACED | WCONTINUED);
		if (ret > 0)
		{
			if (WIFSTOPPED(stat_loc) != 0)
				update_process_status(job_control->job_list, ret, suspended);
			else if (WIFCONTINUED(stat_loc) != 0)
				update_process_status(job_control->job_list, ret, running);
			else
				update_process_status(job_control->job_list, ret, exited);
		}
	}
	update_jobs(job_control);
}
