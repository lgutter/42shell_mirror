/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complete_var.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 05:40:01 by devan         #+#    #+#                 */
/*   Updated: 2020/06/29 05:40:01 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

size_t		complete_var(t_env *env, t_complete *comp)
{
	char *match;

	if (comp->options & VAR_DBRACK)
		match = ft_strdup(&comp->to_complete[2]);
	else
		match = ft_strdup(&comp->to_complete[1]);
	if (match == NULL)
		return (1);
	comp->to_complen = ft_strlen(match);
	while (env != NULL)
	{
		if (ft_strncmp(match, env->key, comp->to_complen) == 0)
			add_complete_list(comp, env->key);
		env = env->next;
	}
	return (0);
}
