/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_pipe_sequence.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 15:49:55 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/08 20:32:54 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
#include "signal_handler.h"
#include <sys/types.h>
#include <stdio.h>
#include "hashtable.h"

static void	exec_in_child(t_pipe_sequence *pipe_seq, t_shell *shell,
							t_job *job, t_process *process)
{
	process->pid = getpid();
	set_process_job_group(job, process);
	if (job->foreground == true && shell->interactive == true)
	{
		tcsetpgrp(STDERR_FILENO, job->pgrp);
		configure_terminal(NULL, 0);
	}
	exit(exec_simple_command(pipe_seq->simple_command, shell));
}

static int	pipe_parent(t_pipe_sequence *pipe_seq, t_shell *shell,
						t_job *job, t_process *process)
{
	int		ret;

	ret = exec_pipe_sequence(pipe_seq->next, shell, job);
	close(STDIN_FILENO);
	handle_new_process(shell, job, process);
	if (process->signal != 0 && process->signal != SIGPIPE)
		print_process_signal(process, sig_print_all);
	return (ret);
}

static int	execute_pipe(t_pipe_sequence *pipe_seq, t_shell *shell,
										t_job *job, t_process *process)
{
	int			pipe_fds[2];

	if (pipe(pipe_fds) != 0)
		return (handle_error(pipe_failure));
	process->pid = fork();
	if (process->pid == 0)
	{
		close(pipe_fds[0]);
		if (dup2(pipe_fds[1], STDOUT_FILENO) < 0)
			exit(handle_error_int(dup2_fd_fail, STDOUT_FILENO));
		exec_in_child(pipe_seq, shell, job, process);
	}
	else if (process->pid > 0)
	{
		set_process_job_group(job, process);
		process->status = running;
		close(pipe_fds[1]);
		if (dup2(pipe_fds[0], STDIN_FILENO) < 0)
			return (handle_error_int(dup2_fd_fail, STDIN_FILENO));
		close(pipe_fds[0]);
		return (pipe_parent(pipe_seq, shell, job, process));
	}
	return (handle_error_str(fork_failure, "while setting up pipe"));
}

static int	execute_simple(t_pipe_sequence *pipe_seq, t_shell *shell,
										t_job *job, t_process *process)
{
	int			ret;

	ret = 0;
	process->pid = fork();
	if (process->pid == 0)
		exec_in_child(pipe_seq, shell, job, process);
	else if (process->pid > 0)
	{
		set_process_job_group(job, process);
		ret = handle_new_process(shell, job, process);
		if (shell->interactive == true && process->signal != 0)
		{
			if (process->pid != job->pgrp)
				print_process_signal(process, sig_print_all);
			else
				print_process_signal(process, sig_print_none);
		}
		return (ret);
	}
	return (handle_error(fork_failure));
}

int			exec_pipe_sequence(t_pipe_sequence *pipe_seq,
								t_shell *shell, t_job *job)
{
	int				old_fds[3];
	int				ret;
	t_process		*process;
	t_simple_cmd	*simple_cmd;

	if (pipe_seq == NULL || shell == NULL || pipe_seq->simple_command == NULL)
		return (parsing_error);
	simple_cmd = pipe_seq->simple_command;
	process = init_process(job, pipe_seq->cmd_string);
	if (process == NULL)
		return (malloc_error);
	set_hash(shell, simple_cmd->argv == NULL ? NULL : simple_cmd->argv[0]);
	std_fd_backup(old_fds);
	if (pipe_seq->pipe == pipe_op)
		ret = execute_pipe(pipe_seq, shell, job, process);
	else if ((simple_cmd->argv != NULL && job->foreground == true &&
	is_builtin(simple_cmd->argv[0]) == true) ||
	(simple_cmd->argv == NULL && simple_cmd->assignments != NULL))
		ret = exec_simple_command(simple_cmd, shell);
	else
		ret = execute_simple(pipe_seq, shell, job, process);
	std_fd_restore(old_fds);
	if (shell->interactive == true)
		tcsetpgrp(STDERR_FILENO, shell->pgid);
	return (ft_setstatus(shell->env, ret));
}
