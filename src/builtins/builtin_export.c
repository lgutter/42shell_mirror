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

static int		print_export(t_shell *shell)
{
	t_env	*head;

	head = shell->env;
	while (head != NULL)
	{
		if ((head->type & ENV_VAR) != 0)
		{
			if (write(STDOUT_FILENO, "", 0) == -1)
			{
				handle_prefix_error_str(bad_fd_error, "export", "write error");
				return (1);
			}
			if (ft_strlen(head->value) == 0)
				ft_printf("export %s%c", head->key, '\n');
			else
				ft_printf("export %s=\"%s\"%c", head->key, head->value, '\n');
		}
		head = head->next;
	}
	return (0);
}

static size_t	checkopt_export(char *arg)
{
	size_t		i;

	i = 1;
	if (arg[0] == '-')
	{
		while (arg[i] != '\0')
		{
			if (arg[0] == '-' && arg[i] != 'p')
			{
				handle_prefix_error_str(invalid_option, "export", arg);
				ft_dprintf(STDERR_FILENO,
										"Usage: export [-p] name[=word]...\n");
				return (1);
			}
			i++;
		}
	}
	return (0);
}

static size_t	export_var(t_env *env, char *arg, char *argz)
{
	char	*var;

	if (ft_strchr(arg, '=') != NULL)
	{
		if (setenv_key_value(env, arg, argz, ENV_VAR) != 0)
			return (1);
	}
	else
	{
		var = ft_getenv(env, arg, SHELL_VAR);
		if (var != NULL)
			if (ft_setenv(env, arg, var, ENV_VAR) != 0)
				return (1);
		if (var == NULL)
			if (ft_setenv(env, arg, "", ENV_VAR) != 0)
				return (1);
		free(var);
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
			return (1);
		}
		if (argv[i][0] != '-')
		{
			print = 0;
			if (export_var(shell->env, argv[i], argv[0]) != 0)
				return (1);
		}
		i++;
	}
	if (print == 1)
		return (print_export(shell));
	return (0);
}
