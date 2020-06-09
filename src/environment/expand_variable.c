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

static size_t	env_str_len(char *string)
{
	size_t	index;

	index = 0;
	while (string[index] == '_' ||
			(string[index] >= 'A' && string[index] <= 'Z') ||
			(string[index] >= 'a' && string[index] <= 'z') ||
			(string[index] >= '0' && string[index] <= '9'))
	{
		index++;
	}
	return (index);
}

static int		abort_dollar(char *key, char **string,
													size_t *read, size_t *write)
{
	int ret;

	ret = 0;
	if (key != NULL)
	{
		(*string)[*write] = '$';
		(*write)++;
	}
	else
		ret = malloc_error;
	free(key);
	return (ret);
}

static int		expand_dollar(t_env *env_list, char **string,
													size_t *read, size_t *write)
{
	char	*key;
	char	*ret;
	char	*value;
	size_t	len;

	len = env_str_len(&((*string)[*read + 1]));
	key = ft_strndup(&((*string)[*read + 1]), len);
	if (key == NULL || len == 0)
		return (abort_dollar(key, string, read, write));
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

int				expand_home(t_env *env_list, char **string,
													size_t *read, size_t *write)
{
	char	*temp;
	char	*value;

	if (string == NULL || *string == NULL || read == NULL || write == NULL)
		return (-1);
	temp = *string;
	if (temp[0] == '~' && (temp[1] == '\0' || temp[1] == '/'))
	{
		value = ft_getenv(env_list, "HOME", VAR_TYPE);
		if (value == NULL)
			return (0);
		temp = ft_strjoin(value, (temp + 1));
		if (temp == NULL)
		{
			free(value);
			return (-1);
		}
		*write += ft_strlen(value);
		*read = *write;
		free(value);
		free(*string);
		*string = temp;
	}
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
