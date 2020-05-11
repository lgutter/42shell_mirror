/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_env_2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/05/08 01:13:03 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "builtins.h"
#include "executor.h"

int				builtin_env(t_command *command, t_env **env)
{
	if (env == NULL || *env == NULL)
		return (0);
	if (((*env)->type & ENV_VAR) != 0)
		ft_printf("%s=%s%c", (*env)->key, (*env)->value, '\n');
	return (builtin_env(command, &(*env)->next));
}

int				builtin_shellenv(t_command *command, t_env **env)
{
	if (env == NULL || *env == NULL)
		return (0);
	if (((*env)->type & SHELL_VAR) != 0)
		ft_printf("%s=%s%c", (*env)->key, (*env)->value, '\n');
	return (builtin_shellenv(command, &(*env)->next));
}