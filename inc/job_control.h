/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   job_control.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 11:43:37 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/08 17:39:44 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include "cetushell.h"
# include <stdbool.h>

typedef	enum			e_status
{
	running = 0,
	suspended,
	broken_pipe,
	exited
}						t_status;

/*
**	options for updating and printing job statuses.
**	these are storen in a single enum to easily pass these options through
**	different functions.
**	brief explanation of all options:
**	job_update_update:	job status will be updated according to process statuses
**	job_update_process:	if status changed, job info will be printed and if
**						status was printed (depending on print options) the job
**						will also be removed from the job list.
**	job_print_auto:		if all process have the same status, job_print_short is
**						used, otherwise job_print_long is used.
**	job_print_short:	The job id, +/-(current/provious), group pid, status
**						and command string are printed on 1 line.
**	job_print_long:		All info for the job is printed, 1 line per process.
**	job_print_pid:		only the job's group pid is printed (script friendly)
**	job_print_pids:		The job id, +/- and all pid's are printed on 1 line.
**	job_print_pid_mask:	used to check if any info about the job will be printed,
**						to be sure we only remove a job if status was printed.
**	job_print_mask:		used to isolate only the printing options. If any of
**						the printing options are enabled, info for the job is
**						always printed.
*/
typedef	enum			e_update_opts
{
	job_update_none = 0,
	job_update_update = (1 << 0),
	job_update_process = (1 << 1),
	job_update_all = (job_update_update | job_update_process),
	job_print_auto = (1 << 2),
	job_print_short = (1 << 3),
	job_print_long = (1 << 4),
	job_print_pid = (1 << 5),
	job_print_pids = (1 << 6),
	job_print_pid_mask = (job_print_pid | job_print_pids),
	job_print_mask = (job_print_auto | job_print_short |
						job_print_pid | job_print_long | job_print_pids)
}						t_update_opts;

typedef	struct			s_job_cont
{
	size_t				current;
	size_t				previous;
	struct s_job		*job_list;
}						t_job_cont;

typedef	struct			s_job
{
	size_t				id;
	pid_t				pgrp;
	t_status			status;
	bool				foreground;
	char				*command;
	struct s_process	*processes;
	struct s_job		*next;
}						t_job;

typedef	struct			s_process
{
	pid_t				pid;
	pid_t				*pgrp;
	t_status			status;
	char				*command;
	struct s_process	*next;
}						t_process;

size_t					get_new_job_id(t_job_cont *job_control);
t_job					*init_job(t_shell *shell, char *command,
															bool foreground);
t_process				*init_process(t_job *job, char *command);
t_status				get_job_status(t_job *job);
t_status				get_status_from_stat_loc(int stat_loc);
void					check_jobs(t_job_cont *job_control, int update_opts);
int						set_process_job_group(t_job *job, t_process *process);

/*
**	update the status of the given job, and print status and remove it from the
**	job list according to the opts argument, which contains one or more of the
**	enum t_update_opts(see comment on t_update_opts).
**	TAKE NOTICE OF RETURN VALUE!
**	args:
**		job_control:	job_control struct for current, previous and removal.
**		job:			the job to be updated/printed.
**		opts:			contains options for updating/printing.
**	returns:
**		this function returns the next job in the list, since it might have
**		deleted the current job. This is VERY important to note in usage, since
**		you might otherwise skip a job if the current one was removed.
*/
t_job					*update_job_status(t_job_cont *job_control,
														t_job *job, int opts);
/*
**	Print information about the given job, in a format depending on the options
**	provided in opts using job_print_* enums from t_update_opts.
**	args:
**		job:		The job for which info should be printed.
**		current:	id for the current job, to determine if + should be printed
**		previous:	id for the previous job, to determine if - should be printed
**		opts:		options for printing, if 0, job_print_auto is assumed.
*/
void					print_job_status(t_job *job,
									size_t current, size_t previous, int opts);
bool					job_spec_match(t_job_cont *job_control,
											t_job *job, const char *job_spec);
void					add_job_to_list(t_shell *shell, t_job *job);
t_job_cont				*free_job_control(t_job_cont *job_control);
t_process				*free_process_list(t_process *start);
t_process				*free_process(t_process *process);
t_job					*free_job_list(t_job *start);
t_job					*free_job(t_job *job);

#endif
