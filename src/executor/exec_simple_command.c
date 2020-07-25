/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_simple_command.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 16:44:21 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/23 14:09:04 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
#include "signal_handler.h"
#include <sys/types.h>
#include <unistd.h>

static void	free_command(t_command *command)
{
	free_dchar_arr(command->envp);
	command->envp = NULL;
	command->argc = 0;
	command->argv = NULL;
	free(command->path);
	command->path = NULL;
}

static int	check_access(char *path)
{
	struct stat statbuf;

	if (access(path, F_OK) != 0)
	{
		exit(handle_error_str(no_such_file_or_dir, path));
	}
	if (access(path, X_OK) != 0)
	{
		exit(handle_error_str(access_denied, path));
	}
	if (stat(path, &statbuf) != 0)
	{
		exit(handle_error_str(access_denied, path));
	}
	if (S_ISDIR(statbuf.st_mode) != 0)
	{
		exit(handle_error_str(is_dir_error, path));
	}
	return (0);
}

static int	init_cmd(t_command *command, t_simple_cmd *simple_cmd, t_env *env)
{
	int ret;

	ret = 0;
	ft_bzero(command, sizeof(command));
	command->argc = str_arr_len(simple_cmd->argv);
	command->argv = simple_cmd->argv;
	command->envp = convert_env_to_envp(env);
	if (command->envp == NULL)
		return (malloc_error);
	ret = find_executable(env, &(command->path), command->argv[0]);
	if (ret != 0)
	{
		if (ret == cmd_not_found)
			handle_error_str(ret, command->argv[0]);
		free_command(command);
	}
	return (ret);
}

void		execve_command(t_command command)
{
	check_access(command.path);
	execve(command.path, command.argv, command.envp);
	exit(handle_error(execve_failure));
}

int			exec_simple_command(t_simple_cmd *simple_cmd, t_shell *shell)
{
	t_command		command;
	int				ret;
	t_redir_info	*redir_info;

	if (simple_cmd == NULL || simple_cmd->argv == NULL || shell == NULL)
		return (parsing_error);
	ret = init_cmd(&command, simple_cmd, shell->env);
	if (ret != 0)
		return (ret);
	else
	{
		redir_info = set_up_redirections(simple_cmd->redirects);
		if (redir_info == NULL)
			return (ret);
		if (is_builtin(simple_cmd->argv[0]) == true)
			ret = execute_builtin(shell, command.argv);
		else if (getpid() == shell->pid)
			return (handle_error_str(internal_error,
											"did not fork for non-builtin"));
		else
			execve_command(command);
	}
	reset_redirections(&redir_info);
	free_command(&command);
	return (ret);
}
