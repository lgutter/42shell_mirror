/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 18:27:10 by devan         #+#    #+#                 */
/*   Updated: 2020/07/23 18:27:10 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static size_t	checkopt_export(char *arg)
{
	size_t		i;

	i = 1;
	if (arg[0] == '-')
	{
		while (arg[i] != '\0')
		{
			if (arg[0] == '-' && arg[i] != 'p')
				return (1);
			i++;
		}
	}
	return (0);
}

static size_t	split_key_value(t_env *env, char *arg)
{
	char	**split;

	split = ft_strsplit(arg, '=');
	if (split == NULL || split[0] == NULL)
		return (handle_error(malloc_error));
	if (ft_setenv(env, split[0], split[1], ENV_VAR) != 0)
	{
		free_dchar_arr(split);
		return (1);
	}
	free_dchar_arr(split);
	return (0);
}

static size_t	export_var(t_env *env, char *arg)
{
	char	*var;
	int		equals;

	equals = ft_countchar(arg, '=');
	if (equals == 1)
		if (split_key_value(env, arg) != 0)
			return (1);
	if (equals == 0)
	{
		var = ft_getenv(env, arg, SHELL_VAR);
		if (var != NULL)
			if (ft_setenv(env, arg, var, ENV_VAR) != 0)
				return (1);
		if (var == NULL)
			if (ft_setenv(env, arg, "", ENV_VAR) != 0)
				return (1);
	}
	else if (equals > 1)
	{
		ft_printf("Invalid Option : Usage: export [-p] name[=word]...\n");
		return (1);
	}
	return (0);
}

int				builtin_export(t_shell *shell, char **argv)
{
	size_t	i;
	int		print;

	i = 1;
	if (argv == NULL || shell == NULL)
		return (1);
	print = 1;
	while (argv[i] != NULL)
	{
		if (checkopt_export(argv[i]) != 0)
		{
			ft_printf("Invalid Option : Usage: export [-p] name[=word]...\n");
			return (1);
		}
		if (argv[i][0] != '-')
		{
			print = 0;
			if (export_var(shell->env, argv[i]) != 0)
				return (1);
		}
		i++;
	}
	if (print == 1)
		print_export(shell, argv);
	return (0);
}
