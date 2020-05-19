/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_env_to_envp.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 10:29:17 by lgutter       #+#    #+#                 */
/*   Updated: 2020/01/20 14:50:05 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static char		*copy_key_value(t_env *env_var)
{
	char	*str;
	size_t	len;
	size_t	index;

	len = ft_strlen(env_var->key) + ft_strlen(env_var->value) + 1;
	str = (char *)ft_memalloc(len + 1);
	if (str == NULL)
		return (NULL);
	index = ft_strlen(env_var->key);
	str[index] = '=';
	index++;
	ft_memcpy(str, env_var->key, ft_strlen(env_var->key));
	ft_memcpy(&(str[index]), env_var->value, ft_strlen(env_var->value));
	return (str);
}

static char		**fill_new_envp(char **envp, t_env *list_start, size_t count)
{
	t_env	*current;
	size_t	index;

	index = 0;
	current = list_start;
	while (index < count && current != NULL)
	{
		envp[index] = copy_key_value(current);
		if (envp[index] == NULL)
		{
			handle_error(malloc_error);
			return (NULL);
		}
		index++;
		current = current->next;
	}
	return (envp);
}

static size_t	get_env_size(t_env *list_start)
{
	t_env	*current;
	size_t	count;

	count = 0;
	current = list_start;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char			**convert_env_to_envp(t_env *list_start)
{
	char	**envp;
	size_t	count;

	count = get_env_size(list_start);
	envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (envp == NULL)
	{
		handle_error(malloc_error);
		return (NULL);
	}
	envp[count] = NULL;
	return (fill_new_envp(envp, list_start, count));
}
