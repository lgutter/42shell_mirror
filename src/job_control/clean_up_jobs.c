/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up_jobs.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 13:50:33 by lgutter       #+#    #+#                 */
/*   Updated: 2020/08/25 13:50:33 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include <signal.h>

void			clean_up_jobs(t_shell *shell)
{
	t_job	*job;

	if (shell != NULL && shell->job_control != NULL)
	{
		check_jobs(shell->job_control, job_update_update);
		job = shell->job_control->job_list;
		while (job != NULL)
		{
			if (get_job_status(job) == suspended)
			{
				kill(-(job->pgrp), SIGKILL);
				ft_dprintf(STDERR_FILENO, "Cetushell: %s %i: %s\n",
								"killed stopped job", job->id, job->command);
			}
			job = job->next;
		}
	}
}
