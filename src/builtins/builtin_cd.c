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
#include "autocomplete.h"
#ifdef __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif
#include "utils.h"

void		follow_links(char **curr, char **input, size_t cur_size)
{
	size_t	i;
	char	*temp;

	i = 0;
	if (input == NULL || cur_size == 0)
		return ;
	while (input[i] != NULL && *curr != NULL)
	{
		if (ft_strcmp(input[i], "..") == 0)
		{
			temp = ft_strndup(*curr, ft_index_nchar(*curr, '/', cur_size));
			free(*curr);
			*curr = ft_strdup(temp);
			free(temp);
			cur_size--;
		}
		else if (ft_strcmp(input[i], ".") != 0)
		{
			str_expand_triple(&*curr, "/", input[i]);
			cur_size++;
		}
		i++;
	}
	free_dchar_arr(input);
}

static int	path_start(t_cd *cd, char *old_pwd)
{
	char	*temp;

	temp = ft_strdup(old_pwd);
	if (cd->input_path[0] != '/' && temp != NULL)
	{
		follow_links(&temp, ft_strsplit(cd->input_path, '/')
								, ft_countchar(old_pwd, '/'));
		if (temp == NULL)
			return (1);
		ft_strncpy(cd->final_path, temp, PATH_MAX);
	}
	else
		ft_strncpy(cd->final_path, cd->input_path, PATH_MAX);
	free(temp);
	return (0);
}

static int	check_change_path(char *path, char *input)
{
	int			ret;

	ret = 0;
	if (access(path, F_OK) != 0)
		ret = no_such_file_or_dir;
	if (ret == 0 && is_directory(NULL, path) == 0)
		ret = not_a_dir_error;
	if (ret == 0 && access(path, X_OK) != 0)
		ret = access_denied;
	if (ret == 0 && chdir(path) == -1)
		ret = chdir_error;
	if (ret != 0)
		handle_prefix_error_str(ret, "cd", input);
	return (ret);
}

static int	resolve_cd_path(t_env *env, t_cd *cd)
{
	char	*old_pwd;
	int		ret;

	ret = 0;
	if (cd->link == true && ft_strlen(cd->link_path) != 0)
		old_pwd = ft_strdup(cd->link_path);
	else if (cd->link == true)
		old_pwd = ft_getenv(env, "PWD", VAR_TYPE);
	else
		old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		ret = 1;
	ret = (ret == 0 ? path_start(cd, old_pwd) : ret);
	ret = (ret == 0 ? check_change_path(cd->final_path, cd->input_path) : ret);
	ret = (ret == 0 ? set_old_new_pwd(env, cd, old_pwd) : ret);
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
	ft_strdel(&(cd_s.input_path));
	ft_bzero(cd_s.final_path, PATH_MAX);
	cd_s.to_oldpwd = false;
	cd_s.to_home = false;
	cd_s.link = true;
	return (ret == 0 ? 0 : 1);
}
