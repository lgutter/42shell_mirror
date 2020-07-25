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

int		ft_setstatus(t_env *env, int error_code)
{
	char	*new;
	int		ret;

	ret = 0;
	new = ft_itoa(error_code);
	if (new == NULL)
		return (malloc_error);
	ret = ft_setenv(env, "?", new, (SHELL_VAR | FORCE_VAR | RO_VAR));
	free(new);
	return (ret);
}

int		ft_getstatus(t_env *env)
{
	char	*temp;
	int		ret;

	temp = ft_getenv(env, "STATUS", SHELL_VAR);
	if (temp == NULL)
		return (0);
	ret = ft_atoi(temp);
	free(temp);
	return (ret);
}
