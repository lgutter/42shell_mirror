/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complete_builtin.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 20:35:52 by devan         #+#    #+#                 */
/*   Updated: 2020/06/29 20:35:52 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"
#include "builtins.h"

size_t		complete_builtin(t_complete *comp)
{
	size_t	i;

	i = 0;
	while (g_builtins[i].builtin_name != NULL)
	{
		if (ft_strncmp(g_builtins[i].builtin_name, comp->to_complete,
						comp->to_complen) == 0)
			add_complete_list(comp, g_builtins[i].builtin_name);
		i++;
	}
	return (0);
}
