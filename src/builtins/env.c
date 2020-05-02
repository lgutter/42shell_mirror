/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: Invalid date        by               #+#    #+#                 */
/*   Updated: Invalid date        by               ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <libft.h>
#include "environment.h"
#include "builtins.h"
#include "executor.h"

int				builtin_env(t_command *command, struct s_env **env)
{
	if (*env == NULL)
		return (0);
	ft_printf("%s=%s%c", (*env)->key, (*env)->value, '\n');
	return (builtin_env(command, &(*env)->next));
}

static int		env_is_valid_key(char *key)
{
	size_t	key_len;
	size_t	i;
	int		is_valid;

	if (key == NULL)
		return (1);
	key_len = ft_strlen(key);
	i = 0;
	while (i < key_len)
	{
		is_valid = (ft_isalnum(key[i]) || key[i] == '_');
		if (i == 0 && ft_isdigit(key[i]))
			is_valid = 0;
		if (!is_valid)
			return (0);
		i++;
	}
	return (1);
}

static int		set_env_or_shell_var(t_env *env, char **key_value, char argzero)
{
	if (ft_strcmp(argzero, "set") == 0)
	{
		if (key_value[1] == NULL)
			return (ft_setenv(env, key_value[0], "", 'y', ENV_VAR));
		else
			return (ft_setenv(env, key_value[0], key_value[1], 'y', ENV_VAR));
	}
	else
	{
		if (key_value[1] == NULL)
			return (ft_setenv(env, key_value[0], "", 'y', SHELL_VAR));
		else
			return (ft_setenv(env, key_value[0], key_value[1], 'y', SHELL_VAR));
	}
}

int				builtin_set(t_command *comm, t_env **env)
{
	int		i;
	char	**key_value;

	i = 1;
	while (i < comm->argc)
	{
		if (ft_strchr(comm->argv[i], '='))
		{
			key_value = ft_strsplit(comm->argv[i], '=');
			if (key_value == NULL || !env_is_valid_key(key_value[0]))
				handle_error_str(set_invalid_name, comm->argv[i]);
			else
			{
				set_env_or_shell_var(env, key_value, comm->argv[0]);
				free_dchar_arr(key_value);
			}
		}
		else
			handle_error_str(set_invalid_name, comm->argv[i]);
		i++;
	}
	return (0);
}

int		builtin_unset(t_command *command, t_env **env)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	while (i < command->argc)
	{
		if (ft_strcmp(command->argv[1], "unset") == 0)
			ret = ft_unsetenv(env, command->argv[i], ENV_VAR);
		else
			ret = ft_unsetenv(env, command->argv[i], SHELL_VAR);
		i++;
	}
	return (0);
}
