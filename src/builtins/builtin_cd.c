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
#include "utils.h"

static char	*follow_links(char *current, char **dest, size_t cur_size)
{
	char	*path;
	size_t	i;
	char	*temp;

	path = ft_strdup(current);
	i = 0;
	while (dest[i] != NULL)
	{
		if (ft_strcmp(dest[i], "..") == 0)
		{
			temp = ft_strndup(path, ft_index_nchar(path, '/', cur_size));
			free(path);
			path = ft_strdup(temp);
			free(temp);
			cur_size--;
		}
		else if (ft_strcmp(dest[i], ".") != 0)
		{
			str_expand_triple(&path, "/", dest[i]);
			cur_size++;
		}
		i++;
	}
	free_dchar_arr(dest);
	return (path);
}

static int	path_start(t_cd *cd, char *old_pwd)
{
	char	*temp;

	if (cd->input_path[0] != '/')
	{
		temp = follow_links(old_pwd, ft_strsplit(cd->input_path, '/')
								, ft_countchar(old_pwd, '/'));
		if (temp == NULL)
			return (1);
		ft_strncpy(cd->final_path, temp, PATH_MAX);
		free(temp);
	}
	else
		ft_strncpy(cd->final_path, cd->input_path, PATH_MAX);
	return (0);
}

static int	resolve_cd_path(t_env *env, t_cd *cd)
{
	char	*old_pwd;
	size_t	ret;

	ret = 0;
	if (cd->link == true && ft_strlen(cd->link_path) != 0)
		old_pwd = ft_strdup(cd->link_path);
	else if (cd->link == true)
		old_pwd = ft_getenv(env, "PWD", VAR_TYPE);
	else
		old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		ret = 1;
	if (ret == 0)
		ret = path_start(cd, old_pwd);
	if (ret == 0 && chdir(cd->final_path) == -1)
		ret = handle_prefix_error_str(no_such_file_or_dir, "cd",
										cd->input_path);
	if (ret == 0)
		ret = set_old_new_pwd(env, cd, old_pwd);
	free(old_pwd);
	return (ret);
}

int			builtin_cd(t_shell *shell, char **argv)
{
	int				ret;
	static t_cd		cd_s = {false, false, true, NULL, "", ""};

	if (shell == NULL || argv == NULL || shell->env == NULL)
		return (1);
	ret = get_cd_options(argv, &cd_s);
	if (ret == 0)
		ret = get_home_oldpw(&cd_s, shell->env);
	if (ret == 0)
		ret = resolve_cd_path(shell->env, &cd_s);
	free(cd_s.input_path);
	ft_bzero(cd_s.final_path, PATH_MAX);
	cd_s = (t_cd){.to_oldpwd = false, .to_home = false, .link = true, };
	return (ret == 0 ? 0 : 1);
}
