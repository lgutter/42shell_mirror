/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/05 12:23:06 by devan         #+#    #+#                 */
/*   Updated: 2020/05/09 23:44:42 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"

int		builtin_exit(t_command *command, t_env *env)
{
	char *prev_status;

	prev_status = ft_getenv(env, "STATUS", SHELL_VAR);
	ft_printf("exit\n");
	configure_terminal(NULL, 0);
	if (command->argc == 1)
		exit(prev_status ? ft_atoi(prev_status) : 0);
	else
		exit(ft_atoi(command->argv[1]));
}
