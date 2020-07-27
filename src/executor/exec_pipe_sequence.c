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
	if (job->foreground == true)
	{
		tcsetpgrp(STDIN_FILENO, job->pgrp);
		configure_terminal(NULL, 0);
	}
	reset_signals();
	exit(exec_simple_command(pipe_seq->simple_command, shell));
}

static void	pipe_parent(t_pipe_sequence *pipe_seq, t_shell *shell,
						t_job *job, t_process *process)
{
	int		stat_loc;
	int		ret;

	exec_pipe_sequence(pipe_seq->next, shell, job);
	close(STDIN_FILENO);
	if (job->foreground == true)
	{
		ret = waitpid(process->pid, &stat_loc, WUNTRACED | WCONTINUED);
		if (ret > 0)
			process->status = get_status_from_stat_loc(stat_loc);
		else if (ret != 0)
			process->status = exited;
	}
	else
		process->status = running;
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
		pipe_parent(pipe_seq, shell, job, process);
		return (0);
	}
	return (handle_error_str(fork_failure, "while setting up pipe"));
}

static int	execute_simple(t_pipe_sequence *pipe_seq, t_shell *shell,
										t_job *job, t_process *process)
{
	int			ret;
	int			stat_loc;

	ret = 0;
	process->pid = fork();
	if (process->pid == 0)
		exec_in_child(pipe_seq, shell, job, process);
	else if (process->pid > 0)
	{
		set_process_job_group(job, process);
		if (job->foreground == true)
		{
			ret = waitpid(process->pid, &stat_loc, WUNTRACED);
			process->status = exited;
			if (ret > 0 && WIFEXITED(stat_loc) != 0)
				ret = ft_setstatus(shell->env, (int)WEXITSTATUS(stat_loc));
			if (ret > 0)
				process->status = get_status_from_stat_loc(stat_loc);
		}
		else
			process->status = running;
		return (ret);
	}
	return (handle_error(fork_failure));
}

int			exec_pipe_sequence(t_pipe_sequence *pipe_seq,
								t_shell *shell, t_job *job)
{
	int			old_fds[3];
	int			ret;
	t_process	*process;

	if (pipe_seq == NULL || pipe_seq->simple_command == NULL ||
		pipe_seq->simple_command->argv == NULL || shell == NULL)
		return (parsing_error);
	set_hash(shell, pipe_seq);
	process = init_process(job, pipe_seq->cmd_string);
	if (process == NULL)
		return (malloc_error);
	std_fd_backup(old_fds);
	if (pipe_seq->pipe == pipe_op)
		ret = execute_pipe(pipe_seq, shell, job, process);
	else if (is_builtin(pipe_seq->simple_command->argv[0]) == true &&
			job->foreground == true)
		ret = exec_simple_command(pipe_seq->simple_command, shell);
	else
		ret = execute_simple(pipe_seq, shell, job, process);
	std_fd_restore(old_fds);
	if (shell->interactive == true)
		tcsetpgrp(STDIN_FILENO, shell->pgid);
	return (ret);
}
