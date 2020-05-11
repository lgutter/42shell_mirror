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
	t_env *current;

	if (key == NULL)
		return (NULL);
	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(key, current->key) == 0 &&
			(opts & (current->type & VAR_TYPE)) != 0)
		{
			return (ft_strdup(current->value));
		}
		current = current->next;
	}
	return (NULL);
}

char	*ft_getenv_quote(t_env *env, const char *key, int opts)
{
	char	*temp;
	char	*unquote;

	temp = ft_getenv(env, key, opts);
	unquote = backslash_quotes(temp);
	free(temp);
	return (unquote);
}
