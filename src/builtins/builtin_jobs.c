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
	opts = (job_print_auto | job_update_all);
	if (argv != NULL && argv[0] != NULL && argv[1] != NULL)
	{
		args = argv[1][0] == '-' ? &(argv[2]) : &(argv[1]);
		if (argv[1][0] == '-' && argv[1][1] == 'l')
			opts = (job_print_long | job_update_all);
		else if (argv[1][0] == '-' && argv[1][1] == 'p')
			opts = (job_print_pid | job_update_print);
	}
	job = shell->job_control->job_list;
	check_jobs(shell->job_control, job_update_none);
	while (job != NULL)
	{
		if (args == NULL || *args == NULL || job_spec_match(shell->job_control, job, args[0]))
			job = update_job_status(shell->job_control, job, opts);
		else
			job = job->next;
	}
	return (0);
}
