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
	char	*temp;
	int		final_code;

	temp = ft_getenv(env, "STATUS", SHELL_VAR);
	configure_terminal(NULL, 0);
	if (command->argc > 1)
		final_code = ft_atoi(command->argv[1]);
	else if (temp == NULL)
		final_code = 0;
	else
		final_code = ft_atoi(temp);
	free(temp);
	temp = ft_itoa(final_code);
	if (temp == NULL)
		ft_setenv(env, "EXIT_CODE", "1", SHELL_VAR | RO_VAR);
	else
		ft_setenv(env, "EXIT_CODE", temp, SHELL_VAR | RO_VAR);
	free(temp);
	return (exit_shell_code);
}
