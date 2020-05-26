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

static int		abort_dollar(char *key, char *ret, char **start, size_t len)
{
	free(ret);
	free(key);
	if (len == 0)
		(*start)++;
	if (len == 0)
		return (0);
	return (-1);
}

static int		expand_dollar(t_env *env_list, char **string, char **start,
								int opts)
{
	char	*key;
	char	*ret;
	char	*value;
	size_t	len;

	ret = ft_strndup(*string, (*start - *string));
	len = env_str_len((*start) + 1);
	key = ft_strndup((*start) + 1, len);
	if (ret == NULL || key == NULL || len == 0)
		return (abort_dollar(key, ret, start, len));
	value = ft_getenv(env_list, key, opts);
	free(key);
	str_expand_triple(&ret, value, (*start) + len + 1);
	if (ret == NULL)
		return (-1);
	if (value == NULL)
		len = 0;
	else
		len = ft_strlen(value);
	*start = ret + (*start - *string) + len;
	free(value);
	free(*string);
	*string = ret;
	return (0);
}

static int		expand_home(t_env *env_list, char **string, int opts)
{
	char	*temp;
	char	*value;
	int		ret;

	ret = 0;
	temp = *string;
	if (temp[0] == '~' && (temp[1] == '\0' || temp[1] == '/'))
	{
		value = ft_getenv(env_list, "HOME", opts);
		if (value != NULL)
		{
			temp = ft_strjoin(value, (temp + 1));
			free(value);
			if (temp == NULL)
				return (-1);
			free(*string);
			*string = temp;
		}
	}
	return (ret);
}

int				expand_variable(t_shell *shell, char **string, int opts)
{
	int		ret;
	char	*offset;
	t_env	*env;

	env = NULL;
	if (shell != NULL)
		env = shell->env;
	if (string == NULL || *string == NULL)
		return (-1);
	ret = 0;
	if ((*string)[0] == '~' && ((*string)[1] == '\0' || (*string)[1] == '/'))
	{
		ret = expand_home(env, string, opts);
		if (ret == -1)
			return (handle_error(malloc_error));
	}
	offset = ft_strchr(*string, '$');
	while (offset != NULL && offset != &(*string)[ft_strlen(*string) - 1])
	{
		ret = expand_dollar(env, string, &offset, opts);
		if (ret == -1)
			return (handle_error(malloc_error));
		offset = ft_strchr(offset, '$');
	}
	return (0);
}
