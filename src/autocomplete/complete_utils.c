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

#include "autocomplete.h"
#include "environment.h"

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
