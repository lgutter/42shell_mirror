/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_hash.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 13:01:57 by devan         #+#    #+#                 */
/*   Updated: 2020/07/28 13:01:57 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "hashtable.h"
#include "executor.h"

static size_t	hash_path(t_shell *shell, char **path, char **split, char *arg)
{
	if (split == NULL || split[0] == NULL)
		return (handle_error(malloc_error));
	if (is_builtin(split[0]) == true)
		return (handle_prefix_error(isbuiltin, split[0]));
	if (split[1] == NULL && ft_strchr(arg, '=') != NULL)
		return (handle_prefix_error(cmd_not_found, arg));
	if (ft_strchr(split[0], '/') != NULL)
		return (handle_prefix_error(cmd_not_found, split[0]));
	if (split[1] == NULL)
	{
		if (find_executable(shell->env, path, arg) != 0)
			return (handle_error_str(cmd_not_found, split[0]));
	}
	else
		*path = ft_strdup(split[1]);
	if (path == NULL)
		return (handle_error(malloc_error));
	return (0);
}

static size_t	hash_args(t_shell *shell, char **argv, size_t i)
{
	char		*path;
	char		**split;
	size_t		ret;

	path = NULL;
	ret = 0;
	split = ft_strsplit(argv[i], '=');
	ret = hash_path(shell, &path, split, argv[i]);
	if (ret == 0 && path != NULL)
		ret = add_to_hash(shell, path, split[0]);
	free(path);
	free_dchar_arr(split);
	return (ret);
}

int				builtin_hash(t_shell *shell, char **argv)
{
	size_t		i;

	if (shell == NULL || argv == NULL)
		return (1);
	i = 1;
	if (argv[i] == NULL)
	{
		print_hashtable(shell->hash);
		return (0);
	}
	else if (ft_strcmp(argv[i], "-i") == 0)
		initialize_hashes(shell);
	else if (ft_strcmp(argv[i], "-r") == 0)
	{
		free_hashtable(shell);
		init_hashtable(shell);
		i++;
	}
	while (argv[i] != NULL && ft_strcmp(argv[1], "-i") != 0)
	{
		if (hash_args(shell, argv, i) != 0)
			return (1);
		i++;
	}
	return (0);
}
