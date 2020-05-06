/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_env.c                                     :+:    :+:            */
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

static int		set_env_or_shell_var(t_env *env, char **key_value, char argzero,
				int read)
{
	int i;

	i = 0;
	if (ft_strcmp(argzero, "set") == 0)
	{
		if (read == 1)
			read == RONLY_ENV;
		else
			read = RW_ENV;
		if (key_value[1] == NULL)
			return (ft_setenv(env, key_value[0], "", RW_ENV));
		else
			return (ft_setenv(env, key_value[0], key_value[1], RW_ENV));
	}
	else
	{
		if (read == 1)
			read == RONLY_SHELL;
		else
			read = RW_SHELL;
		if (key_value[1] == NULL)
			return (ft_setenv(env, key_value[0], "", read));
		else
			return (ft_setenv(env, key_value[0], key_value[1], read));
	}
}

int				resolve_set_values(t_env **env, char *arg, char *argz, int read)
{
	char	**key_value;
	int		ret;

	ret = 0;
	if (ft_strchr(arg, '='))
	{
		key_value = ft_strsplit(arg, '=');
		if (key_value == NULL)
			return (malloc_error);
		if (key_value != NULL && key_value[0] == NULL)
		{
			free_dchar_arr(key_value);
			return (malloc_error);
		}
		if (!env_is_valid_key(key_value[0]))
			return (handle_error_str(set_invalid_key_format, arg));
		else
		{
			ret = set_env_or_shell_var(env, key_value, argz, read);
			free_dchar_arr(key_value);
			return (ret);
		}
	}
	else
		return (handle_error_str(set_invalid_format, arg));
}

int				builtin_set(t_command *comm, t_env **env)
{
	int		i;
	int		ret;
	int		final_ret;

	i = 1;
	final_ret = 0;
	while (i < comm->argc)
	{
		ret = 0;
		if (ft_strcmp(comm->argv[i], "--ronly"))
			ret = 1;
		ret = resolve_set_values(env, comm->argv[1], comm->argv[0], ret);
		if (ret != 0)
			final_ret = ret;
		i++;
	}
	return (final_ret);
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
	return (ret);
}
