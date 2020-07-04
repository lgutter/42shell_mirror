/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complete_var.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 05:40:01 by devan         #+#    #+#                 */
/*   Updated: 2020/07/03 16:26:47 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

static size_t	update_complete_var(t_complete *comp)
{
	char *match;

	if (comp->options & VAR_DBRACK)
		match = ft_strdup(&comp->to_complete[2]);
	else
		match = ft_strdup(&comp->to_complete[1]);
	if (match == NULL)
		return (1);
	comp->to_complen = ft_strlen(match);
	free(comp->to_complete);
	comp->to_complete = match;
	return (0);
}

size_t			complete_var(t_env *env, t_complete *comp)
{
	char	*match;

	if (comp == NULL || comp->to_complete == NULL || comp->options == 0)
		return (1);
	match = NULL;
	update_complete_var(comp);
	while (env != NULL)
	{
		if (ft_strncmp(comp->to_complete, env->key, comp->to_complen) == 0)
		{
			if (comp->options & VAR_DBRACK)
				match = ft_strcharjoin(env->key, '}');
			else
				match = ft_strdup(env->key);
			add_complete_list(comp, match);
			free(match);
			match = NULL;
		}
		env = env->next;
	}
	return (0);
}
