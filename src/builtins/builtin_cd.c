/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/02 19:55:06 by devan         #+#    #+#                 */
/*   Updated: 2020/07/09 18:31:48 by devanando     ########   odam.nl         */
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
	char	*temp;

	ft_bzero(path, PATH_MAX);
	if (getcwd(path, PATH_MAX) == NULL)
	{
		temp = ft_getenv(env, "PWD", ENV_VAR);
		if (temp != NULL)
			ft_strncpy(path, temp, PATH_MAX);
		free(temp);
	}
	if (chdir(new_path) == -1)
	{
		handle_prefix_error_str(no_such_file_or_dir, "cd", new_path);
		return (1);
	}
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

void		get_cd_options(char **argv, char *path)
{
	struct s_ft_getopt  opti = {0, 1, 1, 0, false};
	bool				link;
	char				*path;

	link = true;
	while (ft_getopt(&opti, ft_str_arr_len(argv), argv, "LP"))
	{
		if (opti.opt == 'L')
			link = true;
		else if (opti.opt == 'P')
			link = false;
	}
	path = ft_strdup(argv[opti.index]);
	ft_printf("\n Test ===, link(%d), %s\n", link, path);
	if (opti.illegal)
		ft_printf("\nerror\n");
}

// int			builtin_cd(t_shell *shell, char **argv)
// {
// 	long long 		options;
// 	char			*path;

// 	get_cd_options();

// }

int			builtin_cd(t_command *command, t_env *env)
{
	char	*key;
	char	*temp;
	int		ret;
	int		argc;
	struct s_ft_getopt opt;

	ret = 0;
	temp = NULL;
	get_cd_options(command->argv);
	if (command == NULL || command->argv == NULL)
		return (-1);
	argc = ft_str_arr_len(command->argv);




	
	key = (argc == 1) ? "HOME" : "OLDPWD";
	if (argc > 4)
		ret = handle_prefix_error(too_many_arguments, "cd");
	else if (argc == 1 || ft_strcmp(argv[1], "-") == 0)
	{
		temp = ft_getenv(shell->env, key, VAR_TYPE);
		if (temp == NULL)
			ret = handle_prefix_error_str(var_not_set, "cd", key);
	}
	else
		temp = ft_strdup(command->argv[1]);
	if (ret == 0 && temp == NULL)
		ret = handle_error(malloc_error);
	if (ret == 0)
		ret = cd(env, temp, command->argv[1]);
	free(temp);
	return (ret == 0 ? 0 : 1);
}
