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

static void	update_process_status(t_job *start, pid_t pid, int stat_loc)
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
				process->status = get_status_from_stat_loc(stat_loc, process);
				if (process->signal != 0)
				{
					ft_dprintf(STDERR_FILENO, "%i %s\n",
									process->pid, sys_siglist[process->signal]);
				}
				return ;
			}
			process = process->next;
		}
		job = job->next;
	}
}

void		check_jobs(t_job_cont *job_control, int update_opts)
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
			update_process_status(job_control->job_list, ret, stat_loc);
		}
	}
	job = job_control->job_list;
	while (update_opts != job_update_none && job != NULL)
		job = update_job_status(job_control, job, update_opts);
}
