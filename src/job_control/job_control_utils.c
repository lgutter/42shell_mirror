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

void			print_process_signal(t_process *process, t_sig_print_opts opts)
{
	if (process != NULL && process->signal != 0)
	{
		if (process->signal != SIGINT)
		{
			if ((opts & sig_print_pid) == sig_print_pid)
				ft_dprintf(STDERR_FILENO, "%i: ", process->pid);
			ft_dprintf(STDERR_FILENO, "%s", sys_siglist[process->signal]);
			if ((opts & sig_print_command) == sig_print_command)
				ft_dprintf(STDERR_FILENO, "\t%s", process->command);
		}
		process->signal = 0;
		ft_dprintf(STDERR_FILENO, "\n");
	}
}

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

int				set_process_job_group(t_job *job, t_process *process)
{
	if (job == NULL || process == NULL)
		return (-1);
	if (job->pgrp == 0)
		job->pgrp = process->pid;
	setpgid(process->pid, job->pgrp);
	return (0);
}
