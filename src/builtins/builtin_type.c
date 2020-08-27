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

static bool	type_write_error(bool *error)
{
	if (*error != true && write(STDOUT_FILENO, "", 0) == -1)
	{
		*error = true;
		handle_prefix_error_str(bad_fd_error, "type", "write error");
	}
	return (*error);
}

static int	type_executable(t_shell *shell, char *path, bool *error)
{
	char	*check;
	int		ret;

	ret = 0;
	check = NULL;
	find_executable(shell == NULL ? NULL : shell->env, &check, path);
	if (check != NULL &&
			(ft_strchr(check, '/') == NULL || is_executable(check) == true))
	{
		if (type_write_error(error) == true)
			ret = 1;
		else
			ft_printf("%s is %s\n", path, check);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "%s not found\n", path);
		ret = 1;
	}
	free(check);
	return (ret);
}

int			builtin_type(t_shell *shell, char **argv)
{
	size_t	i;
	int		ret;
	bool	error;

	if (argv == NULL || argv[0] == NULL)
		return (1);
	ret = 0;
	i = 1;
	error = false;
	while (argv[i] != NULL)
	{
		if (is_builtin(argv[i]) == true && type_write_error(&error) == false)
			ft_printf("%s is a shell builtin\n", argv[i]);
		else
		{
			if (type_executable(shell, argv[i], &error) != 0)
				ret = 1;
		}
		i++;
	}
	return (ret);
}
