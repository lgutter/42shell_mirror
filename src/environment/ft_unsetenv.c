/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsetenv.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 20:08:17 by lgutter       #+#    #+#                 */
/*   Updated: 2020/02/07 13:15:06 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static int	remove_first(t_env *first)
{
	t_env *second;

	if (first->next == NULL)
	{
		free(first->key);
		free(first->value);
		first->key = ft_strdup("");
		first->value = ft_strdup("");
		if (first->key == NULL || first->value == NULL)
			return (handle_error(malloc_error));
	}
	else
	{
		second = first->next;
		free(first->key);
		first->key = second->key;
		free(first->value);
		first->value = second->value;
		first->next = second->next;
		free(second);
	}
	return (0);
}

int			ft_unsetenv(t_env *env, const char *key)
{
	t_env	*current;
	t_env	*previous;

	previous = env;
	if (key == NULL)
		return (-1);
	if (env == NULL)
		return (handle_error(env_empty_error));
	if (ft_strcmp(previous->key, key) == 0)
		return (remove_first(previous));
	while (previous != NULL)
	{
		if (previous->next != NULL &&
			ft_strcmp((previous->next)->key, key) == 0)
			break ;
		previous = previous->next;
	}
	if (previous == NULL)
		return (env_not_found);
	current = previous->next;
	free(current->key);
	free(current->value);
	previous->next = current->next;
	free(current);
	return (0);
}
