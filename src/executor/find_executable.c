/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_executable.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/30 10:34:10 by lgutter       #+#    #+#                 */
/*   Updated: 2020/01/30 15:08:18 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	find_exec_in_dir(char *dirname, char *exec_name)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(dirname);
	if (dir == NULL)
		return (-1);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strcmp(entry->d_name, exec_name) == 0)
		{
			(void)closedir(dir);
			return (0);
		}
		entry = readdir(dir);
	}
	(void)closedir(dir);
	return (-1);
}

static int	traverse_paths(char **paths, t_command *command, char *arg_zero)
{
	size_t	index;

	index = 0;
	while (paths[index] != NULL)
	{
		command->path = NULL;
		if (find_exec_in_dir(paths[index], arg_zero) == 0)
		{
			if (paths[index][ft_strlen(paths[index]) - 1] != '/')
				ft_strexpand(&(paths[index]), "/");
			command->path = ft_strjoin(paths[index], arg_zero);
			if (command->path == NULL)
				return (handle_error(malloc_error));
			else if (access(command->path, X_OK) == 0)
				return (0);
			else
				free(command->path);
		}
		index++;
	}
	command->path = NULL;
	return (handle_error_str(cmd_not_found, arg_zero));
}

int			find_executable(t_env *env_list, t_command *command, char *arg_zero)
{
	char	*env_path;
	char	**paths;
	int		ret;

	ret = 0;
	if (command == NULL || arg_zero == NULL)
		return (parsing_error);
	command->path = NULL;
	if (ft_strchr(arg_zero, '/') != NULL)
		command->path = ft_strdup(arg_zero);
	else
	{
		env_path = ft_getenv(env_list, "PATH", VAR_TYPE);
		if (env_path == NULL)
			return (handle_error_str(env_not_found, "PATH"));
		paths = ft_strsplit(env_path, ':');
		free(env_path);
		if (paths == NULL)
			return (handle_error(malloc_error));
		ret = traverse_paths(paths, command, arg_zero);
		free_dchar_arr(paths);
	}
	return (ret);
}
