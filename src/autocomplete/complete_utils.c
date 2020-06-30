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
	char			joinedforces[PATH_MAX];

	if (file == NULL || path == NULL)
		return (1);
	ft_snprintf(joinedforces, PATH_MAX, "%s/%s", path, file);
	if (joinedforces == NULL)
		return (1);
	if (lstat(file, &statbuff) == -1)
		return (1);
	if (S_ISDIR(statbuff.st_mode))
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
	if (getcwd(curdir, PATH_MAX) == NULL)
		temp = ft_getenv(env, "PWD", ENV_VAR);
	else
		temp = ft_strdup(curdir);
	return (temp);
}
