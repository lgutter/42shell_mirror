/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setenv_key_value.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/30 11:49:39 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/30 11:49:39 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	env_is_valid_key(char *key)
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
			return (false);
		i++;
	}
	return (true);
}

int			setenv_key_value(t_env *env, char *arg, char *argz, int opts)
{
	char	*key;
	char	*value;
	int		ret;

	if (arg == NULL)
		return (-1);
	key = ft_strndup(arg, (ft_strchr(arg, '=') - arg));
	value = ft_strdup(ft_strchr(arg, '=') + 1);
	if (key == NULL || value == NULL)
		ret = handle_error(malloc_error);
	else
	{
		if (env_is_valid_key(key) == false)
			ret = handle_prefix_error_str(error_inv_format, argz, key);
		else
		{
			ret = ft_setenv(env, key, value, opts);
			if (ret != 0)
				handle_prefix_error_str(ret, argz, key);
		}
	}
	free(key);
	free(value);
	return (ret);
}
