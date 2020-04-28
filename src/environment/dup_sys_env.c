/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dup_sys_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:35:25 by lgutter       #+#    #+#                 */
/*   Updated: 2020/02/10 16:45:21 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static t_env	*new_env_list_item(char *env_variable)
{
	t_env		*new;

	new = (t_env *)ft_memalloc(sizeof(t_env) * 1);
	if (new == NULL)
	{
		handle_error(malloc_error);
		return (NULL);
	}
	else
	{
		new->key = ft_strcdup(env_variable, '=');
		new->value = ft_strdup(&(
	env_variable[ft_strlenc(env_variable, '=', ft_strlen(env_variable)) + 1]));
		if (new->key == NULL || new->value == NULL)
		{
			free(new->key);
			free(new->value);
			handle_error(malloc_error);
			return (NULL);
		}
	}
	new->next = NULL;
	return (new);
}

static t_env	*empty_env_init(void)
{
	t_env	*new;

	new = (t_env *)ft_memalloc(sizeof(t_env) * 1);
	if (new == NULL)
	{
		handle_error(malloc_error);
		return (NULL);
	}
	else
	{
		new->key = ft_strdup("PWD");
		new->value = getcwd(NULL, 0);
		if (new->key == NULL || new->value == NULL)
		{
			free(new->key);
			free(new->value);
			handle_error(malloc_error);
			return (NULL);
		}
	}
	new->next = NULL;
	return (new);
}

t_env			*dup_sys_env(void)
{
	extern char	**environ;
	size_t		index;
	t_env		*start;
	t_env		*current;

	index = 0;
	if (environ == NULL || environ[0] == NULL)
		return (empty_env_init());
	current = new_env_list_item(environ[index]);
	if (current == NULL)
	{
		handle_error(malloc_error);
		return (NULL);
	}
	start = current;
	index++;
	while (environ[index] != NULL)
	{
		current->next = new_env_list_item(environ[index]);
		current = current->next;
		if (current == NULL)
			return (NULL);
		index++;
	}
	return (start);
}