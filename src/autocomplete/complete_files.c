/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complete_files.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 20:58:06 by devan         #+#    #+#                 */
/*   Updated: 2020/06/29 20:58:06 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"
#include "ft_printf.h"
#include "environment.h"
#include <dirent.h>
#include <unistd.h>

static char		*resolve_complete(t_complete *comp)
{
	int		i;
	char	*complete;

	i = (int)comp->to_complen - 1;
	if (comp->to_complen != 0)
		while (comp->to_complete[i] != '/' && i > -1)
			i--;
	if (i < 0)
		complete = ft_strdup(comp->to_complete);
	else if ((i == 0 && comp->to_complete[0] != '/') || comp->to_complen != 0 ||
				(comp->to_complen == 2 && comp->to_complete[i] == '/'))
		complete = ft_strdup("");
	else
		complete = ft_strdup(&comp->to_complete[i + 1]);
	return (complete);
}

static char		*resolve_path(t_complete *comp, char *curdir)
{
	char			*temp;
	char			path[PATH_MAX];
	int				i;

	ft_bzero(path, PATH_MAX);
	i = (int)comp->to_complen - 1;
	if (comp->to_complen != 0)
		while (comp->to_complete[i] != '/' && i > -1)
			i--;
	if (comp->to_complen == 1 && comp->to_complete[0] == '.')
		temp = ft_strdup("");
	else if ((int)comp->to_complen - 1 == i)
		temp = ft_strdup(comp->to_complete);
	else
		temp = ft_strndup(comp->to_complete,
				(comp->to_complen - (comp->to_complen - (i + 1))));
	if (temp == NULL)
		return (NULL);
	if (comp->to_complen > 0 && comp->to_complete[0] == '/')
		ft_strncpy(path, temp, PATH_MAX);
	else if (curdir != NULL)
		ft_snprintf(path, PATH_MAX, "%s/%s", curdir, temp);
	free(temp);
	temp = ft_strdup(path);
	return (temp);
}

static size_t	filter_files(t_complete *comp, char *file, char *path)
{
	if ((comp->options & FILES) == 0)
	{
		if (is_directory(file, path) != 0)
			return (1);
	}
	if ((ft_strlen(file) == 1 && file[0] == '.') || (ft_strlen(file) == 2
			&& ft_strncmp(file, "..", 2) == 0))
		return (1);
	return (0);
}

static size_t	add_file_match(t_complete *comp, char *path, char *complete)
{
	DIR				*directory;
	struct dirent	*files;
	char			*temp;

	directory = opendir(path);
	if (directory == NULL)
		return (1);
	files = readdir(directory);
	while (files != NULL)
	{
		if (strncmp(complete, files->d_name, ft_strlen(complete)) == 0)
		{
			if (filter_files(comp, files->d_name, path) == 0 &&
					is_directory(files->d_name, path) != 0)
				add_complete_list(comp, files->d_name);
			else if (is_directory(files->d_name, path) == 0)
			{
				temp = ft_strjoin(files->d_name, "/");
				add_complete_list(comp, temp);
				free(temp);
			}
		}
		files = readdir(directory);
	}
	return (closedir(directory));
}

size_t			complete_files(t_env *env, t_complete *comp)
{
	char			*path;
	char			*curdir;
	char			*complete;

	if (comp == NULL || comp->to_complete == NULL || env == NULL)
		return (1);
	curdir = get_shell_cwd(env);
	if (curdir == NULL)
		return (1);
	complete = resolve_complete(comp);
	path = resolve_path(comp, curdir);
	free(curdir);
	if (path == NULL || complete == NULL)
		return (1);
	if (add_file_match(comp, path, complete) != 0)
		return (1);
	free(path);
	free(complete);
	return (0);
}
