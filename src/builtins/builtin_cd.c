/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/02 19:55:06 by devan         #+#    #+#                 */
/*   Updated: 2020/05/02 19:55:06 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

static int	cd(t_env **env, char *new_path)
{
	char	old_path[PATH_MAX];

	getcwd(old_path, PATH_MAX);
	if (old_path == NULL)
		return (1);
	if (chdir(new_path) == -1)
		return (1);
	if (ft_setenv(env, "OLDPWD", old_path, 'y') != 0)
		return (1);
	if (ft_setenv(env, "PWD", new_path, 'y') != 0)
		return (1);
	return (0);
}

int			builtin_cd(t_command *command, t_env *env)
{
	char	new_path[PATH_MAX];
	char	*temp;

	if (command->argc > 2)
		return (to_many_arguments);
	if (command->argc == 1)
	{
		temp = t_getenv(command->envp, "HOME");
		if (temp == NULL)
			return (error_shell_variable_home);
		ft_strlcpy(new_path, temp, PATH_MAX);
	}
	else if (ft_strcmp(command->argv[1], "-") == 0)
	{
		temp = ft_getenv(env, "OLDPWD");
		if (temp == NULL)
			return (error_shell_variable_oldpwd);
		ft_strlcpy(new_path, temp, PATH_MAX);
		ft_printf("%s\n", new_path);
	}
	else
		ft_strlcpy(new_path, command->argv[1], PATH_MAX);
	return (cd(env, new_path));
}
