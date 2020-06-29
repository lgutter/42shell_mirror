/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_complete.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: devanando <devanando@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 21:56:01 by devanando     #+#    #+#                 */
/*   Updated: 2020/06/24 15:22:05 by devanando     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input_handling.h"
#include "cetushell.h"
#include "autocomplete.h"
#include "handle_error.h"
/*
 * structure:
 * When tab pressed:
 * 1. check input give options back 
 *      > cd        : only directories
 *      > ""        : executables in PATH + builtins
 *      > "ascii"   : current dir
 *      > $ or ${}  : env + internal variables 
 * 2. check possibilities complete(dir, options)
 *      > 1 match               :complete 
 *      > fit screen 1+ match   : create matrix / selection
 *      > small creen 1+ match  : create matrix / set viewcoordinates / selection with scrolling matrix
 * 
*/

size_t		free_complete(t_complete *com, size_t ret)
{
	com = (void *)com;
	return (ret);
}

static size_t		complete(t_shell *shell, t_complete *comp)
{
	comp->list = (t_clist*)ft_memalloc(sizeof(t_clist));
	if (comp->list == NULL)
		handle_error(malloc_error);
	// if (comp->options & (1 << BUILTINS))
	// 	complete_builtins();
	if (comp->options & EXECUTABLES)
		if (complete_exec(comp, shell->env) != 0)
			return (1);
	// if (comp->options & (1 << DIRECTORIES) || comp->options & (1 << FILES))
	// 	complete_files();
	if ((comp->options & VAR_DOLLAR) ||
		(comp->options & VAR_DBRACK))
		if (complete_var(shell->env, comp) != 0)
			return (1);
	debug_complete_list(comp);
	return (0);
}

size_t			auto_complete(t_shell *shell)
{
	t_complete	comp;

	ft_memset((void *)&comp, 0, sizeof(t_complete));
	if (initialize_complete(&comp, shell->buffer) != 0)
		return (handle_error(free_complete(&comp, malloc_error)));
	if (complete(shell, &comp) != 0)
		return (free_complete(&comp, 1));
	free_complete(&comp, 0);
	return (0);
}
