/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_hashpath.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/27 01:21:35 by devan         #+#    #+#                 */
/*   Updated: 2020/07/27 01:21:35 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "builtins.h"

static void	open_dirs(t_shell *shell, char *path)
{
	DIR				*directory;
	struct dirent	*files;
	char			*temp;

	directory = opendir(path);
	temp = ft_strdup(path);
	if (directory == NULL || temp == NULL)
		return ;
	files = readdir(directory);
	while (files != NULL && temp != NULL)
	{
		str_expand_triple(&temp, "/", files->d_name);
		if (temp != NULL && is_executable(temp) != 0 &&
				hash_duplicate(files->d_name, shell->hash) == 0)
			add_to_hash(shell, temp, files->d_name);
		free(temp);
		temp = ft_strdup(path);
		files = readdir(directory);
	}
	free(temp);
	closedir(directory);
}

void		initialize_hashes(t_shell *shell)
{
	char	*path;
	char	**split;
	size_t	i;

	i = 0;
	if (shell == NULL || shell->env == NULL)
		return ;
	path = ft_getenv(shell->env, "PATH", VAR_TYPE);
	if (path == NULL)
		return ;
	split = ft_strsplit(path, ':');
	free(path);
	if (split == NULL)
		return ;
	while (split[i] != NULL)
	{
		open_dirs(shell, split[i]);
		i++;
	}
	free_dchar_arr(split);
}
