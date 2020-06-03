/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_set.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/05/10 00:36:28 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "builtins.h"
#include "executor.h"

static int		env_is_valid_key(char *key)
{
	size_t	key_len;
	size_t	i;
	int		is_valid;

	key_len = ft_strlen(key);
	i = 0;
	while (i < key_len)
	{
		is_valid = (ft_isalnum(key[i]) || key[i] == '_');
		if (i == 0 && ft_isdigit(key[i]))
			is_valid = 0;
		if (is_valid == 0)
			return (0);
		i++;
	}
	return (1);
}

static char **	get_key_value(char *arg)
{
	char	**key_value;
	char	**temp;

	key_value = ft_strsplit(arg, '=');
	if (key_value == NULL || key_value[0] == NULL)
	{
		free_dchar_arr(key_value);
		return (NULL);
	}
	if (key_value[1] == NULL)
	{
		temp = ft_memalloc(sizeof(char *) * 3);
		if (temp == NULL)
			return (NULL);
		temp[0] = key_value[0];
		temp[1] = ft_strdup("");
		free(key_value);
		key_value = temp;
	}
	return (key_value);
}

static int		resolve_set_values(t_env *env, char *arg, char *argz, int opts)
{
	char	**key_value;
	int		ret;

	ret = 0;
	key_value = get_key_value(arg);
	if (key_value == NULL)
		ret = malloc_error;
	else if (key_value[2] == NULL)
	{
		if (env_is_valid_key(key_value[0]) == 0)
			ret = handle_prefix_error_str(error_inv_format, argz, key_value[0]);
		else
		{
			ret = ft_setenv(env, key_value[0], key_value[1], opts);
			if (ret != 0)
				handle_prefix_error_str(ret, argz, key_value[0]);
		}
	}
	else
		ret = handle_prefix_error_str(error_inv_format, argz, arg);
	free_dchar_arr(key_value);
	return (ret);
}

static int		get_set_opts(char **argv, int *i)
{
	int		opts;

	opts = (ft_strcmp(argv[0], "setenv") == 0) ? ENV_VAR : SHELL_VAR;
	while (argv[*i] != NULL && argv[*i][0] == '-' && argv[*i][1] == '-')
	{
		if (ft_strcmp(argv[*i], "--help") == 0)
		{
			ft_dprintf(2, "Usage: %s [OPTION]... [KEY=VALUE]...\n\n", argv[0]);
			ft_dprintf(2, "Options:\n\t--help:\tprint this usage.\n");
			ft_dprintf(2, "\t--readonly:\tvariables are made read only.\n");
			ft_dprintf(2, "\t--force:\tread only attributes are ignored.\n");
			return (-1);
		}
		else if (ft_strcmp(argv[*i], "--readonly") == 0)
			opts |= RO_VAR;
		else if (ft_strcmp(argv[*i], "--force") == 0)
			opts |= FORCE_VAR;
		else
		{
			handle_prefix_error_str(invalid_option, argv[0], argv[*i]);
			return (-1);
		}
		(*i)++;
	}
	return (opts);
}

int				builtin_set(t_command *comm, t_env *env)
{
	int		i;
	int		ret;
	int		opts;

	i = 1;
	ret = 0;
	if (comm == NULL || env == NULL ||
		comm->argv == NULL || comm->argv[0] == NULL)
		return (-1);
	if (comm->argc == 1)
	{
		if (ft_strcmp(comm->argv[0], "setenv") == 0)
			return (builtin_env(comm, env));
		return (builtin_shellenv(comm, env));
	}
	opts = get_set_opts(comm->argv, &i);
	if (opts < 0)
		return (1);
	while (i < comm->argc && comm->argv[i] != NULL)
	{
		if (resolve_set_values(env, comm->argv[i], comm->argv[0], opts) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
