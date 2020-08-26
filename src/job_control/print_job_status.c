/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_job_status.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/17 14:42:17 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/17 14:42:17 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

const char	*g_job_statuses[4] = {
	[running] = "running",
	[suspended] = "suspended",
	[broken_pipe] = "broken pipe",
	[exited] = "exited"
};

static bool	job_has_single_status(t_job *job)
{
	t_process *process;

	process = job->processes;
	while (process != NULL)
	{
		if (process->status != job->status)
			return (false);
		process = process->next;
	}
	return (true);
}

static void	print_long_job_status(t_job *job, char prefix[9])
{
	t_process	*process;

	process = job->processes;
	while (process != NULL)
	{
		ft_printf("%s%-6i %-11s  %s\n", prefix,
			process->pid, g_job_statuses[process->status], process->command);
		process = process->next;
		ft_snprintf(prefix, 8, "        ");
	}
}

static void	print_job_pids(t_job *job, char prefix[9])
{
	t_process	*process;

	process = job->processes;
	if (process == NULL)
		return ;
	ft_printf("%s", prefix);
	while (process != NULL)
	{
		ft_printf("%-6lu ", process->pid);
		process = process->next;
	}
	ft_printf("\n");
}

void		print_job_status(t_job *job, size_t current, size_t previous,
															t_update_opts opts)
{
	char		prefix[9];
	char		curprev;

	if (job == NULL)
		return ;
	if (job->id == current)
		curprev = '+';
	else
		curprev = job->id == previous ? '-' : ' ';
	ft_snprintf(prefix, 8, "[%i] %c   ", job->id, curprev);
	prefix[8] = '\0';
	if ((opts & job_print_auto) != 0 || opts == 0)
		opts |= job_has_single_status(job) ? job_print_short : job_print_long;
	if ((opts & job_print_long) != 0)
		print_long_job_status(job, prefix);
	else if ((opts & job_print_short) != 0)
		ft_printf("%s%-6i %-11s  %s\n",
			prefix, job->pgrp, g_job_statuses[job->status], job->command);
	else if ((opts & job_print_pid) != 0)
		ft_printf("%i\n", job->pgrp);
	else if ((opts & job_print_pids) != 0)
		print_job_pids(job, prefix);
}
