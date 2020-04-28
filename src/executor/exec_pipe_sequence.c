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

static int	execute_pipe(t_pipe_sequence *pipe_seq, t_env *env_list)
{
	int		pipe_fds[2];
	pid_t	child_pid;
	int		*stat_loc;

	stat_loc = NULL;
	if (pipe(pipe_fds) != 0)
		return (handle_error(pipe_failure));
	child_pid = fork();
	if (child_pid == 0)
	{
		close(pipe_fds[0]);
		dup2(pipe_fds[1], STDOUT_FILENO);
		exit(exec_simple_command(pipe_seq->simple_command, env_list));
	}
	else if (child_pid > 0)
	{
		close(pipe_fds[1]);
		dup2(pipe_fds[0], STDIN_FILENO);
		exec_pipe_sequence(pipe_seq->next, env_list);
		waitpid(child_pid, stat_loc, 0);
		close(pipe_fds[0]);
		return (0);
	}
	return (handle_error_str(fork_failure, "while setting up pipe"));
}

int			exec_pipe_sequence(t_pipe_sequence *pipe_seq, t_env *env_list)
{
	int		*old_fds;
	int		ret;

	std_fd_backup(&old_fds);
	if (pipe_seq == NULL || pipe_seq->simple_command == NULL)
		return (-1);
	if (pipe_seq->pipe == pipe_op)
	{
		ret = execute_pipe(pipe_seq, env_list);
	}
	else
	{
		ret = exec_simple_command(pipe_seq->simple_command, env_list);
		std_fd_restore(&old_fds);
		if (pipe_seq->next != NULL)
			ret = exec_pipe_sequence(pipe_seq->next, env_list);
	}
	std_fd_restore(&old_fds);
	return (ret);
}
