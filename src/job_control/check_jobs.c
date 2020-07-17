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

void		check_jobs(t_job_cont *job_control)
{
	t_job	*job;
	int		stat_loc;
	int		ret;

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
	job = job_control->job_list;
	while (job != NULL)
		job = update_job_status(job_control, job,
										(job_update_remove | job_update_print));
}
