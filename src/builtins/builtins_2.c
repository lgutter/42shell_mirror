/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/05 12:23:06 by devan         #+#    #+#                 */
/*   Updated: 2020/05/05 12:23:06 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"

int		builtin_exit(t_command *command, t_env **env)
{
	char *prev_status;

	prev_status = ft_getenv(env, "STATUS");
	if (command->argc == 1)
		exit(prev_status ? ft_atoi(prev_status) : 0);
	else
		exit(ft_atoi(command->argv[1]));
}
