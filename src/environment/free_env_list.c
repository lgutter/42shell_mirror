/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_env_list.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 14:01:30 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/10 00:35:56 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

int		free_env_list(t_env *env_list)
{
	t_env *current;
	t_env *previous;

	current = env_list;
	while (current != NULL)
	{
		previous = current;
		current = current->next;
		free(previous->key);
		previous->key = NULL;
		free(previous->value);
		previous->value = NULL;
		previous->type = 0;
		free(previous);
		previous = NULL;
	}
	return (0);
}
