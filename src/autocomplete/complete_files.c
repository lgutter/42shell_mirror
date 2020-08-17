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
		while (i > -1 && comp->to_complete[i] != '/')
			i--;
	if (i < 0)
		complete = ft_strdup(comp->to_complete);
	else if ((i == 0 && comp->to_complete[0] != '/') ||
				(comp->to_complen == 2 && comp->to_complete[i] == '/'))
		complete = ft_strdup("");
	else
		complete = ft_strdup(&comp->to_complete[i + 1]);
	return (complete);
}

static char		*resolve_path(t_env *env, t_complete *comp, size_t complen)
{
	int		i;
	char	*path;
	char	*curdir;

	curdir = get_shell_cwd(env);
	if (curdir == NULL)
		return (NULL);
	if (comp->to_complete != NULL && comp->to_complete[0] == '/')
	{
		free(curdir);
		curdir = ft_strdup(comp->to_complete);
	}
	else
		follow_links(&curdir, ft_strsplit(comp->to_complete,
			'/'), ft_countchar(curdir, '/'));
	if (curdir == NULL)
		return (NULL);
	i = ft_strlen(curdir) - 1;
	if (complen != 0)
		while (i > -1 && curdir[i] != '/')
			i--;
	path = ft_strndup(curdir, i + 1);
	free(curdir);
	return (path);
}

static size_t	filter_files(t_complete *comp, char *file, char *path)
{
	if ((comp->options & FILES) == 0)
	{
		if (is_directory(file, path) == false)
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
					is_directory(files->d_name, path) == false)
				add_complete_list(comp, files->d_name);
			else if (is_directory(files->d_name, path) == true)
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
	char			*complete;
	size_t			ret;

	ret = 0;
	if (comp == NULL || comp->to_complete == NULL || env == NULL)
		return (1);
	complete = resolve_complete(comp);
	if (complete == NULL)
		return (1);
	path = resolve_path(env, comp, ft_strlen(complete));
	if (path == NULL)
		ret = 1;
	if (ret != 0 || add_file_match(comp, path, complete) != 0)
		ret = 1;
	free(path);
	free(complete);
	return (ret);
}
