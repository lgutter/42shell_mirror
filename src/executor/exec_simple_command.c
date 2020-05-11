/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_simple_command.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 16:44:21 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/28 16:44:21 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"

static int	check_access(t_env *env_list, char *path)
{
	struct stat statbuf;

	if (access(path, F_OK) != 0)
	{
		ft_setstatus(env_list, no_such_file_or_dir);
		return (handle_error_str(no_such_file_or_dir, path));
	}
	if (access(path, X_OK) != 0)
	{
		ft_setstatus(env_list, access_denied);
		return (handle_error_str(access_denied, path));
	}
	if (stat(path, &statbuf) != 0)
	{
		ft_setstatus(env_list, access_denied);
		return (handle_error_str(access_denied, path));
	}
	if (S_ISDIR(statbuf.st_mode) != 0)
	{
		ft_setstatus(env_list, access_denied);
		return (handle_error_str(is_dir_error, path));
	}
	return (0);
}

static int	execute_command(t_env *env_list, t_command *command)
{
	int		stat_loc;
	int		ret;
	pid_t	pid;

	ret = check_access(env_list, command->path);
	if (ret == 0)
	{
		configure_terminal(NULL, 0);
		pid = fork();
		if (pid == 0)
		{
			execve(command->path, command->argv, command->envp);
			exit(handle_error(execve_failure));
		}
		else if (pid > 0)
		{
			waitpid(pid, &stat_loc, 0);
			if (ft_setstatus(env_list, WEXITSTATUS(stat_loc)) != 0)
				ret = WEXITSTATUS(stat_loc);
		}
		else
			ret = handle_error(fork_failure);
	}
	return (ret);
}

static void	free_command(t_command *command)
{
	free_dchar_arr(command->envp);
	command->envp = NULL;
	command->argc = 0;
	command->argv = NULL;
	free(command->path);
	command->path = NULL;
}

static int	init_cmd(t_command *command, t_simple_cmd *simple_cmd, t_env *env)
{
	ft_bzero(command, sizeof(command));
	command->argc = str_arr_len(simple_cmd->argv);
	command->argv = simple_cmd->argv;
	command->envp = convert_env_to_envp(env);
	if (command->envp == NULL)
		return (malloc_error);
	return (find_executable(env, command, command->argv[0]));
}

int			exec_simple_command(t_simple_cmd *simple_cmd, t_env *env)
{
	t_command		command;
	int				ret;
	t_redir_info	*redir_info;

	if (simple_cmd == NULL || simple_cmd->argv == NULL || env == NULL)
		return (parsing_error);
	ret = init_cmd(&command, simple_cmd, env);
	if (ret != 0)
		return (ret);
	else
	{
		redir_info = set_up_redirections(simple_cmd->redirects);
		if (redir_info != NULL)
		{
			if (command.path[0] != '\0')
				ret = execute_command(env, &command);
			else
				ret = execute_builtin(&command, env);
		}
	}
	reset_redirections(&redir_info);
	free_command(&command);
	return (ret);
}
