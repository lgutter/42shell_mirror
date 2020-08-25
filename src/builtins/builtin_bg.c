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

static void	print_bg_error(t_job *job)
{
	char *error;

	if (get_job_status(job) == running)
		error = "is already running";
	else
		error = "has exited";
	ft_dprintf(STDERR_FILENO, "Cetushell: bg: job %i %s\n", job->id, error);
}

static void	update_background_job(t_job *job)
{
	size_t	len;
	char	*command;

	command = job->command;
	len = ft_strlen(command);
	job->foreground = false;
	if (command[len - 1] == '\n' ||
		command[len - 1] == ';')
	{
		command[len - 1] = '&';
	}
	else if (command[len - 1] != '&')
		ft_strexpand(&(job->command), " &");
}

static bool	iterate_jobs(t_job_cont *job_control, char *job_spec)
{
	t_job	*job;
	bool	job_found;

	job_found = false;
	job = job_control->job_list;
	check_jobs(job_control, job_update_none);
	while (job != NULL)
	{
		if (job_spec_match(job_control, job, job_spec) == true)
		{
			job_found = true;
			if (get_job_status(job) == suspended)
			{
				kill(-(job->pgrp), SIGCONT);
				if (job->foreground == true)
					update_background_job(job);
			}
			else
				print_bg_error(job);
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
