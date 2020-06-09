/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_pipe_sequence.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 15:49:55 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/28 15:49:55 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <signal.h>
#include <sys/types.h>

static int	parent_wait(int pipe_fds[2], t_pipe_sequence *pipe_seq,
						pid_t child_pid, t_env *env)
{
	int		ret;

	ret = 0;
	close(pipe_fds[1]);
	if (dup2(pipe_fds[0], STDIN_FILENO) < 0)
	{
		ret = handle_error_int(dup2_fd_fail, STDIN_FILENO);
	}
	else
	{
		ret = exec_pipe_sequence(pipe_seq->next, env);
		kill(child_pid, SIGTERM);
	}
	close(pipe_fds[0]);
	return (ret);
}

static int	execute_pipe(t_pipe_sequence *pipe_seq, t_env *env_list)
{
	int		pipe_fds[2];
	pid_t	child_pid;

	if (pipe(pipe_fds) != 0)
		return (handle_error(pipe_failure));
	child_pid = fork();
	if (child_pid == 0)
	{
		close(pipe_fds[0]);
		if (dup2(pipe_fds[1], STDOUT_FILENO) < 0)
			exit(handle_error_int(dup2_fd_fail, STDOUT_FILENO));
		exit(exec_simple_command(pipe_seq->simple_command, env_list));
	}
	else if (child_pid > 0)
	{
		return (parent_wait(pipe_fds, pipe_seq, child_pid, env_list));
	}
	return (handle_error_str(fork_failure, "while setting up pipe"));
}

int			exec_pipe_sequence(t_pipe_sequence *pipe_seq, t_env *env_list)
{
	int		old_fds[3];
	int		ret;

	if (pipe_seq == NULL || pipe_seq->simple_command == NULL)
		return (parsing_error);
	std_fd_backup(old_fds);
	if (pipe_seq->pipe == pipe_op)
	{
		ret = execute_pipe(pipe_seq, env_list);
	}
	else
	{
		ret = exec_simple_command(pipe_seq->simple_command, env_list);
		if (pipe_seq->next != NULL)
			ret = handle_error_str(parsing_error,
								"no pipe operator, but more pipe sequences");
	}
	std_fd_restore(old_fds);
	return (ret);
}
