/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_jobs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 16:23:35 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/16 16:23:35 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	iterate_jobs(t_job_cont *job_control, char *job_spec, int opts)
{
	t_job	*job;
	bool	job_found;

	job_found = false;
	job = job_control->job_list;
	while (job != NULL)
	{
		if (job_spec_match(job_control, job, job_spec) == true)
		{
			job_found = true;
			job = update_job_status(job_control, job, opts);
		}
		else
			job = job->next;
	}
	return (job_found);
}

static int	iterate_job_specs(char **args, t_job_cont *job_control, int opts)
{
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	while (args[i] != NULL)
	{
		if (iterate_jobs(job_control, args[i], opts) == false)
		{
			ret = 1;
			handle_prefix_error_str(job_not_found, "jobs", args[i]);
		}
		i++;
	}
	return (ret);
}

int			builtin_jobs(t_shell *shell, char **argv)
{
	char	**args;
	t_job	*job;
	int		opts;

	if (shell == NULL || shell->job_control == NULL)
		return (1);
	args = NULL;
	opts = (job_print_auto | job_update_all);
	if (argv != NULL && argv[0] != NULL && argv[1] != NULL)
	{
		args = argv[1][0] == '-' ? &(argv[2]) : &(argv[1]);
		if (argv[1][0] == '-' && argv[1][1] == 'l')
			opts = (job_print_long | job_update_all);
		else if (argv[1][0] == '-' && argv[1][1] == 'p')
			opts = (job_print_pid | job_update_process);
	}
	check_jobs(shell->job_control, job_update_none);
	if (args != NULL && args[0] != NULL)
		return (iterate_job_specs(args, shell->job_control, opts));
	job = shell->job_control->job_list;
	while (job != NULL)
		job = update_job_status(shell->job_control, job, opts);
	return (0);
}
