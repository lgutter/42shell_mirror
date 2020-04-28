/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_setenv.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 16:03:54 by lgutter       #+#    #+#                 */
/*   Updated: 2020/01/13 20:52:34 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static int	fill_emptied_element(t_env *env, const char *key, const char *value)
{
	free(env->key);
	free(env->value);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	if (env->key == NULL || env->value == NULL)
	{
		handle_error(malloc_error);
		return (-1);
	}
	return (0);
}

static int	addenv(t_env *env, const char *key, const char *value)
{
	t_env *current;
	t_env *new;

	current = env;
	if (current == NULL)
		return (handle_error(env_empty_error));
	if (ft_strcmp(env->key, "") == 0 && ft_strcmp(env->value, "") == 0)
		return (fill_emptied_element(env, key, value));
	new = (t_env *)ft_memalloc(sizeof(t_env) * 1);
	if (new != NULL)
	{
		new->key = ft_strdup(key);
		new->value = ft_strdup(value);
	}
	if (new == NULL || new->key == NULL || new->value == NULL)
	{
		return (handle_error(malloc_error));
	}
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	return (0);
}

int			ft_setenv(t_env *env, const char *key,
										const char *value, char overwrite)
{
	t_env *current;

	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			if (overwrite == 'y')
			{
				free(current->value);
				current->value = ft_strdup(value);
				if (current->value == NULL)
				{
					return (handle_error(malloc_error));
				}
				return (0);
			}
			return (handle_error(env_write_error));
		}
		current = current->next;
	}
	return (addenv(env, key, value));
}