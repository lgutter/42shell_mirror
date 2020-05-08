/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsetenv.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 20:08:17 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/07 23:02:32 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static void	free_env_element(t_env *env)
{
	free(env->key);
	env->key = NULL;
	free(env->value);
	env->value = NULL;
	env->type = 0;
}

static int	remove_first(t_env *first, int type)
{
	t_env *second;

	if ((RO_VAR & first->type) != 0 && (type & FORCE_VAR) == 0)
		return (error_ronly);
	if (first->next == NULL)
	{
		free_env_element(first);
		first->key = ft_strdup("");
		first->value = ft_strdup("");
		if (first->key == NULL || first->value == NULL)
			return (handle_error(malloc_error));
	}
	else
	{
		second = first->next;
		free_env_element(first);
		first->key = second->key;
		first->value = second->value;
		first->type = second->type;
		first->next = second->next;
		free(second);
	}
	return (0);
}

int			ft_unsetenv(t_env *env, const char *key, int type)
{
	t_env	*current;

	if (key == NULL)
		return (-1);
	if (env == NULL)
		return (handle_error(env_empty_error));
	if (ft_strcmp(env->key, key) == 0 &&
		(type & (env->type & VAR_TYPE)) != 0)
		return (remove_first(env, type));
	while (env != NULL)
	{
		if (env->next != NULL && ft_strcmp((env->next)->key, key) == 0 &&
			(type & ((env->next)->type & VAR_TYPE)) != 0)
			break ;
		env = env->next;
	}
	if (env == NULL)
		return (env_not_found);
	current = env->next;
	if ((RO_VAR & current->type) != 0 && (type & FORCE_VAR) == 0)
		return (error_ronly);
	free_env_element(current);
	env->next = current->next;
	free(current);
	return (0);
}
