/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_fg.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/21 12:14:37 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/21 12:14:37 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "signal_handler.h"
#include <signal.h>

static t_job	*get_matchingjob(t_job_cont *job_control, char *job_spec)
{
	t_job	*job;
	t_job	*match;

	if (job_control == NULL)
		return (NULL);
	match = NULL;
	job = job_control->job_list;
	while (job != NULL)
	{
		if (job_spec_match(job_control, job, job_spec) == true)
		{
			if (match != NULL)
			{
				handle_prefix_error_str(ambig_job_spec, "fg", job_spec);
				return (NULL);
			}
			match = job;
		}
		job = job->next;
	}
	if (match == NULL)
		handle_prefix_error_str(job_not_found, "fg", job_spec);
	return (match);
}

static void		continue_job(t_shell *shell, t_job *job)
{
	t_status	status;

	job->status = running;
	status = job->status;
	tcsetpgrp(STDERR_FILENO, job->pgrp);
	configure_terminal(NULL, 0);
	kill(-(job->pgrp), SIGCONT);
	while (status == job->status)
	{
		check_jobs(shell->job_control, job_update_none);
		status = get_job_status(job);
	}
	check_jobs(shell->job_control, job_update_all);
	tcsetpgrp(STDERR_FILENO, shell->pgid);
	configure_terminal(shell, 3);
}

int				builtin_fg(t_shell *shell, char **argv)
{
	t_job		*job;

	if (shell == NULL || argv == NULL || argv[0] == NULL)
		return (1);
	if (shell->interactive == false)
		return (handle_error(no_job_control) != 0);
	job = get_matchingjob(shell->job_control, argv[1] == NULL ? "%+" : argv[1]);
	if (job == NULL)
		return (1);
	job->foreground = true;
	print_job_status(job, shell->job_control->current,
								shell->job_control->previous, job_print_short);
	continue_job(shell, job);
	return (0);
}
