/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complete_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/01 01:03:01 by devan         #+#    #+#                 */
/*   Updated: 2020/07/01 01:03:01 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include "autocomplete.h"
#include "environment.h"

size_t		is_directory(char *file, char *path)
{
	struct stat		statbuff;
	char			complete_path[PATH_MAX];

	if (file == NULL || path == NULL)
		return (1);
	ft_snprintf(complete_path, PATH_MAX, "%s/%s", path, file);
	if (lstat(complete_path, &statbuff) == -1)
		return (1);
	if (S_ISDIR(statbuff.st_mode) || S_ISLNK(statbuff.st_mode))
		return (0);
	return (1);
}

char		*get_shell_cwd(t_env *env)
{
	char			curdir[PATH_MAX];
	char			*temp;

	if (env == NULL)
		return (NULL);
	ft_bzero(curdir, PATH_MAX);
	temp = ft_getenv(env, "PWD", ENV_VAR);
	if (temp == NULL)
	{
		if (getcwd(curdir, PATH_MAX) == NULL)
			return (NULL);
		temp = ft_strdup(curdir);
	}
	return (temp);
}
