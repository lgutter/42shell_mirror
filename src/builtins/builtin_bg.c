/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_bg.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/21 12:14:37 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/21 12:14:37 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <signal.h>

static bool	iterate_jobs(t_job_cont *job_control, char *job_spec)
{
	t_job	*job;
	bool	job_found;

	job_found = false;
	job = job_control->job_list;
	while (job != NULL)
	{
		if (job_spec_match(job_control, job, job_spec) == true)
		{
			kill(-(job->pgrp), SIGCONT);
			job_found = true;
			if (job->foreground == true)
			{
				job->foreground = false;
				ft_strexpand(&(job->command), " &");
			}
		}
		job = job->next;
	}
	return (job_found);
}

int			builtin_bg(t_shell *shell, char **argv)
{
	size_t	i;
	int		ret;
	char	*job_spec;

	if (shell == NULL || shell->job_control == NULL ||
		argv == NULL || argv[0] == NULL)
		return (1);
	i = 1;
	ret = 0;
	job_spec = argv[i];
	if (job_spec == NULL)
		job_spec = "%+";
	while (job_spec != NULL)
	{
		if (iterate_jobs(shell->job_control, job_spec) == false)
		{
			ret = 1;
			handle_prefix_error_str(job_not_found, "bg", job_spec);
		}
		if (argv[i] != NULL)
			i++;
		job_spec = argv[i];
	}
	return (ret);
}
