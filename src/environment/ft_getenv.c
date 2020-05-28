/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_getenv.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 15:49:17 by lgutter       #+#    #+#                 */
/*   Updated: 2020/02/04 21:37:31 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

char	*ft_getenv(t_env *env, const char *key, int opts)
{
	t_env	*current;
	char	*temp;

	if (key == NULL)
		return (NULL);
	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(key, current->key) == 0 &&
			(opts & (current->type & VAR_TYPE)) != 0)
		{
			if ((opts & QUOTE_VAR) != 0)
				temp = backslash_quotes(current->value);
			else
				temp = ft_strdup(current->value);
			return (temp);
		}
		current = current->next;
	}
	return (NULL);
}
