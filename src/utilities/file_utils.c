/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/03 16:09:27 by devan         #+#    #+#                 */
/*   Updated: 2020/08/03 16:09:27 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

bool		is_executable(char *path)
{
	struct stat statbuff;

	if (path == NULL)
		return (false);
	if (stat(path, &statbuff) != 0)
		return (false);
	if (access(path, X_OK) != 0)
		return (false);
	return (S_ISREG(statbuff.st_mode));
}

bool		is_directory(char *file, char *path)
{
	struct stat		statbuff;
	char			complete_path[PATH_MAX];

	if (path == NULL)
		return (false);
	if (file != NULL)
		ft_snprintf(complete_path, PATH_MAX, "%s/%s", path, file);
	else
		ft_strcpy(complete_path, path);
	if (stat(complete_path, &statbuff) == -1)
		return (false);
	return (S_ISDIR(statbuff.st_mode));
}
