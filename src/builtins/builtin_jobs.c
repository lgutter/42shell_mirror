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

int			builtin_jobs(char **argv, t_shell *shell)
{
	t_job	*job;
	char	**args;
	int		opts;

	if (shell == NULL || shell->job_control == NULL)
	{
		handle_prefix_error_str(internal_error, "jobs",
							"Shell struct passed to jobs is invalid");
		return (1);
	}
	args = NULL;
	opts = job_print_auto;
	if (argv != NULL && argv[0] != NULL && argv[1] != NULL)
	{
		args = argv[1][0] == '-' ? &(argv[2]) : &(argv[1]);
		if (argv[1][0] == '-' && argv[1][1] == 'l')
			opts = job_print_long;
		else if (argv[1][0] == '-' && argv[1][1] == 'p')
			opts = job_print_pid;
	}
	job = shell->job_control->job_list;
	while (job != NULL)
	{
		job = update_job_status(shell->job_control, job, job_update_none);
		if (args == NULL || *args == NULL || job_spec_match(shell->job_control, job, args[0]))
			print_job_status(job, shell->job_control->current,
								shell->job_control->previous, opts);
		job = update_job_status(shell->job_control, job, job_update_all);
	}
	return (0);
}
