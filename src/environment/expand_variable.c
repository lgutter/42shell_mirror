/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_variable.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/21 12:13:49 by lgutter       #+#    #+#                 */
/*   Updated: 2020/02/15 13:24:13 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static ssize_t	env_str_len(char *string)
{
	size_t	index;

	index = 0;
	if (string[index] == '{')
		index++;
	if (string[index] == '?')
		index++;
	while (string[index] == '_' ||
			(string[index] >= 'A' && string[index] <= 'Z') ||
			(string[index] >= 'a' && string[index] <= 'z') ||
			(string[index] >= '0' && string[index] <= '9'))
	{
		index++;
	}
	if (string[0] == '{' && string[index] == '}')
		index++;
	else if (string[0] == '{')
		return (-1);
	return (index);
}

static int		abort_dollar(char *key, char **string,
													size_t *write, ssize_t len)
{
	int ret;

	ret = 0;
	if (key != NULL)
	{
		(*string)[*write] = '$';
		(*write)++;
	}
	else if (len >= 0)
		ret = malloc_error;
	else
		ret = bad_subst_err;
	free(key);
	return (ret);
}

static char		*get_variable_key(char *string, size_t read, ssize_t len)
{
	char *temp;

	if (len < 0)
	{
		len = env_str_len(&(string[read + 2]));
		temp = ft_strndup(&(string[read]), 2 + len);
		handle_error_str(bad_subst_err, temp);
		free(temp);
		return (NULL);
	}
	temp = string + read + 1;
	if (temp[0] == '{')
	{
		temp++;
		len -= 2;
	}
	return (ft_strndup(temp, len));
}

static int		expand_dollar(t_env *env_list, char **string,
													size_t *read, size_t *write)
{
	char	*key;
	char	*ret;
	char	*value;
	ssize_t	len;

	len = env_str_len(&((*string)[*read + 1]));
	key = get_variable_key(*string, *read, len);
	if (key == NULL || len <= 0)
		return (abort_dollar(key, string, write, len));
	ret = ft_strndup(*string, (*write));
	if (ret == NULL)
		return (malloc_error);
	value = ft_getenv(env_list, key, VAR_TYPE);
	free(key);
	str_expand_triple(&ret, value, &(*string)[*read + len + 1]);
	if (ret == NULL)
		return (malloc_error);
	len = ft_strlen(value);
	*write += len;
	*read = *write - 1;
	free(value);
	free(*string);
	*string = ret;
	return (0);
}

int				expand_variable(t_shell *shell, char **string,
													size_t *read, size_t *write)
{
	int		ret;
	t_env	*env;

	env = (shell != NULL) ? shell->env : NULL;
	if (string == NULL || *string == NULL || read == NULL || write == NULL)
		return (-1);
	ret = 0;
	ret = expand_dollar(env, string, read, write);
	if (ret == malloc_error)
		handle_error(malloc_error);
	return (ret);
}
