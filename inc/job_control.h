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
	exited
}						t_status;

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
void					check_jobs(t_job_cont *job_control);
int						set_process_job_group(t_job *job, t_process *process);
void					print_job_status(t_job *job,
												size_t current, size_t prev);
void					add_job_to_list(t_shell *shell, t_job *job);
t_job_cont				*free_job_control(t_job_cont *job_control);
t_process				*free_process_list(t_process *start);
t_process				*free_process(t_process *process);
t_job					*free_job_list(t_job *start);
t_job					*free_job(t_job *job);

#endif