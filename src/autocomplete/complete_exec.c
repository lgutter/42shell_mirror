/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complete_exec.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 13:53:11 by devan         #+#    #+#                 */
/*   Updated: 2020/06/29 13:53:11 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"
#include <dirent.h>
#include <unistd.h>

static size_t	match_exec(t_complete *comp, char *path)
{
	DIR				*directory;
	struct dirent	*files;

	directory = opendir(path);
	if (directory == NULL)
		return (handle_error(readdir_error));
	files = readdir(directory);
	while (files != NULL)
	{
		if (ft_strncmp(comp->to_complete, files->d_name, comp->to_complen) == 0)
			add_complete_list(comp, files->d_name);
		files = readdir(directory);
	}
	(void)closedir(directory);
	return (0);
}

size_t			complete_exec(t_env *env, t_complete *comp)
{
	char			*paths;
	char			**path;
	size_t			i;

	i = 0;
	paths = ft_getenv(env, "PATH", VAR_TYPE);
	if (paths == NULL)
		return (handle_error(env_not_found));
	path = ft_strsplit(paths, ':');
	free(paths);
	if (path != NULL)
	{
		while (path[i] != NULL)
		{
			match_exec(comp, path[i]);
			i++;
		}
	}
	free_dchar_arr(path);
	return (0);
}
