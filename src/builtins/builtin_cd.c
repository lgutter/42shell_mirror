/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/02 19:55:06 by devan         #+#    #+#                 */
/*   Updated: 2020/05/10 00:10:06 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"
#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

static int	cd(t_env *env, char *new_path, char *key)
{
	char	path[PATH_MAX];

	ft_bzero(path, PATH_MAX);
	getcwd(path, PATH_MAX);
	if (chdir(new_path) == -1)
		return (1);
	if (key != NULL && ft_strcmp(key, "-") == 0)
		ft_printf("%s\n", new_path);
	if (ft_setenv(env, "OLDPWD", path, ENV_VAR) != 0)
		return (1);
	ft_bzero(path, PATH_MAX);
	getcwd(path, PATH_MAX);
	if (ft_setenv(env, "PWD", path, ENV_VAR) != 0)
		return (1);
	return (0);
}

int			builtin_cd(t_command *command, t_env *env)
{
	char	*key;
	char	*temp;
	int		ret;

	key = (command->argc == 1) ? "HOME" : "OLDPWD";
	if (command->argc > 2)
		return (handle_prefix_error(too_many_arguments, "cd"));
	if (command->argc == 1 || ft_strcmp(command->argv[1], "-") == 0)
	{
		temp = ft_getenv(env, key, VAR_TYPE);
		if (temp == NULL)
		{
			handle_prefix_error_str(var_not_set, "cd", key);
			return (1);
		}
	}
	else
		temp = ft_strdup(command->argv[1]);
	if (temp == NULL)
		return (handle_error(malloc_error));
	ret = cd(env, temp, command->argv[1]);
	if (ret != 0)
		handle_prefix_error_str(no_such_file_or_dir, "cd", temp);
	free(temp);
	return (ret);
}
