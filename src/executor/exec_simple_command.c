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

static int	check_access(t_env *env_list, char *path)
{
	struct stat statbuf;

	if (access(path, F_OK) != 0)
	{
		//ft_setstatus(env_list, no_such_file_or_dir);
		return (handle_error_str(no_such_file_or_dir, path));
	}
	if (access(path, X_OK) != 0)
	{
		//ft_setstatus(env_list, access_denied);
		return (handle_error_str(access_denied, path));
	}
	if (stat(path, &statbuf) != 0)
	{
		//ft_setstatus(env_list, access_denied);
		return (handle_error_str(access_denied, path));
	}
	if (S_ISDIR(statbuf.st_mode) != 0)
	{
		//ft_setstatus(env_list, access_denied);
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
			//if (ft_setstatus(env_list, WEXITSTATUS(stat_loc)) != 0)
			ret = WEXITSTATUS(stat_loc);
		}
		else
			ret = handle_error(fork_failure);
	}
	return (ret);
}

static int	execute_builtin(t_env *env_list, t_command *command)
{
	int	ret;

	ret = -1;
	ft_printf("BUILTIN!\n");
	// if (ft_strcmp(command->argv[0], "cd") == 0)
	// 	ret = ft_cd_builtin(env_list, command);
	// else if (ft_strcmp(command->argv[0], "echo") == 0)
	// 	ret = ft_echo_builtin(env_list, command);
	// else if (ft_strcmp(command->argv[0], "exit") == 0)
	// 	ft_exit_builtin(env_list, command);
	// else if (ft_strcmp(command->argv[0], "env") == 0)
	// 	ret = ft_env_builtin(env_list, command);
	// else if (ft_strcmp(command->argv[0], "setenv") == 0)
	// 	ret = ft_setenv_builtin(env_list, command);
	// else if (ft_strcmp(command->argv[0], "unsetenv") == 0)
	// 	ret = ft_unsetenv_builtin(env_list, command);
	// else if (ft_strcmp(command->argv[0], "setshell") == 0)
	// 	ret = ft_setshell_builtin(env_list, command);
	// else if (ft_strcmp(command->argv[0], "unsetshell") == 0)
	// 	ret = ft_unsetshell_builtin(env_list, command);
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

int			exec_simple_command(t_simple_cmd *simple_cmd, t_env *env_list)
{
	t_command		command;
	int				ret;
	t_redir_info	*redir_info;

	if (simple_cmd == NULL || simple_cmd->argv == NULL || env_list == NULL)
		return (parsing_error);
	command.argc = str_arr_len(simple_cmd->argv);
	command.argv = simple_cmd->argv;
	ret = find_executable(env_list, &command, command.argv[0]);
	if (ret != 0)
		return (ret);
	command.envp = convert_env_to_envp(env_list);
	if (command.envp == NULL || command.path == NULL)
		return (handle_error(malloc_error));
	redir_info = set_up_redirections(simple_cmd->redirects);
	if (command.path[0] != '\0')
		ret = execute_command(env_list, &command);
	else
		ret = execute_builtin(env_list, &command);
	reset_redirections(&redir_info);
	free_command(&command);
	return (ret);
}
