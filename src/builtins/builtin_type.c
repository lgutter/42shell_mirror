/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_type.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 21:31:32 by devan         #+#    #+#                 */
/*   Updated: 2020/07/23 21:31:32 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	is_executable(char *path)
{
	struct stat statbuff;

	if (stat(path, &statbuff) != 0)
		return (false);
	if (access(path, X_OK) != 0)
		return (false);
	return (S_ISREG(statbuff.st_mode));
}

static int	type_executable(t_shell *shell, char *path)
{
	char	*check;
	int		ret;

	ret = 0;
	check = NULL;
	find_executable(shell == NULL ? NULL : shell->env, &check, path);
	if (check != NULL &&
			(ft_strchr(check, '/') == NULL || is_executable(check) == true))
	{
		ft_printf("%s is %s\n", path, check);
		ret = 0;
	}
	else
	{
		ft_printf("%s not found\n", path);
		ret = 1;
	}
	free(check);
	return (ret);
}

int			builtin_type(t_shell *shell, char **argv)
{
	size_t	i;
	int		ret;

	if (argv == NULL || argv[0] == NULL)
		return (1);
	ret = 0;
	i = 1;
	while (argv[i] != NULL)
	{
		if (is_builtin(argv[i]) == true)
			ft_printf("%s is a shell builtin\n", argv[i]);
		else
		{
			if (type_executable(shell, argv[i]) != 0)
				ret = 1;
		}
		i++;
	}
	return (ret);
}
