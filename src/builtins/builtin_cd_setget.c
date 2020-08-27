/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd_setget.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/19 20:10:33 by devan         #+#    #+#                 */
/*   Updated: 2020/07/19 20:10:33 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

int				get_cd_options(char **argv, t_cd *cd_s)
{
	struct s_ft_getopt	opt;
	int					len;

	if (argv == NULL || cd_s == NULL)
		return (1);
	len = (int)ft_str_arr_len(argv) - 1;
	opt = (struct s_ft_getopt){NULL, 1, 1, 0, false};
	while (ft_getopt(&opt, len + 1, argv, "LP"))
	{
		if (opt.opt == 'L')
			cd_s->link = true;
		else if (opt.opt == 'P')
			cd_s->link = false;
	}
	if (opt.illegal)
		return (1);
	if (argv[opt.index] == NULL || ft_strcmp(argv[opt.index], "~") == 0)
		cd_s->to_home = true;
	else
		cd_s->input_path = ft_strdup(argv[opt.index]);
	if (opt.index < len && argv[opt.index + 1] != NULL && cd_s->to_home != 1)
		return (handle_prefix_error(too_many_arguments, "cd"));
	if (cd_s->input_path != NULL && ft_strcmp(cd_s->input_path, "-") == 0)
		cd_s->to_oldpwd = true;
	return (0);
}

int				get_home_oldpw(t_cd *cd_s, t_env *env)
{
	char	*key;

	if (cd_s == NULL || env == NULL)
		return (1);
	if (cd_s->to_oldpwd == true || cd_s->to_home == true)
	{
		key = ft_getenv(env, (cd_s->to_oldpwd ? "OLDPWD" : "HOME"), 3);
		if (key == NULL)
		{
			return (handle_prefix_error_str(var_not_set,
				"cd", cd_s->to_oldpwd ? "OLDPWD" : "HOME"));
		}
		free(cd_s->input_path);
		cd_s->input_path = ft_strdup(key);
		free(key);
		if (cd_s->input_path == NULL)
			return (handle_error(malloc_error));
	}
	return (0);
}

static int	print_old_pwd(char *path)
{
	if (write(STDOUT_FILENO, "", 0) == -1)
		return (handle_prefix_error_str(bad_fd_error, "cd", "write error"));
	ft_printf("%s\n", path);
	return (0);
}

int			set_old_new_pwd(t_env *env, t_cd *cd, char *old_path)
{
	if (env == NULL || cd == NULL || old_path == NULL)
		return (1);
	if (cd->link == true)
	{
		if (ft_setenv(env, "OLDPWD", (ft_strlen(cd->link_path) == 0 ?
							old_path : cd->link_path), ENV_VAR))
			return (handle_prefix_error(malloc_error, "cd"));
		ft_bzero(cd->link_path, PATH_MAX);
		ft_strncpy(cd->link_path, cd->final_path, PATH_MAX);
		if (ft_setenv(env, "PWD", cd->link_path, ENV_VAR))
			return (handle_prefix_error(malloc_error, "cd"));
	}
	else
	{
		ft_bzero(cd->link_path, PATH_MAX);
		if (getcwd(cd->link_path, PATH_MAX) == NULL)
			return (handle_prefix_error(getcwd_error, "cd"));
		if (ft_setenv(env, "OLDPWD", old_path, ENV_VAR) != 0 ||
			ft_setenv(env, "PWD", cd->link_path, ENV_VAR) != 0)
			return (handle_prefix_error(malloc_error, "cd"));
	}
	if (cd->to_oldpwd)
		return (print_old_pwd(cd->link ? cd->link_path : cd->final_path));
	return (0);
}
