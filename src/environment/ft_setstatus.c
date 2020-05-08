/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_setstatus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/08 19:14:17 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/08 19:14:17 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

int		ft_setstatus(t_env *env, t_error error_code)
{
	char *new;

	new = ft_itoa(error_code);
	if (new == NULL)
		return (malloc_error);
	return (ft_setenv(env, "STATUS", new, (SHELL_VAR | FORCE_VAR | RO_VAR)));
}
