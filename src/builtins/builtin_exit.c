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

int		builtin_exit(t_shell *shell, char **argv)
{
	char	*temp;
	int		final_code;

	if (shell == NULL)
		return (exit_shell_code);
	if (shell->job_control != NULL && shell->job_control->job_list != NULL)
	{
		ft_dprintf(STDERR_FILENO, "Cetushell: you have unfinished jobs.\n");
		return (0);
	}
	temp = ft_getenv(shell->env, "?", SHELL_VAR);
	if (shell->interactive == true)
		configure_terminal(NULL, 0);
	if (argv != NULL && argv[0] != NULL && argv[1] != NULL)
		final_code = ft_atoi(argv[1]);
	else
		final_code =  (temp == NULL) ? 0 : ft_atoi(temp);
	free(temp);
	temp = ft_itoa(final_code);
	if (temp == NULL)
		ft_setenv(shell->env, "EXIT_CODE", "1", SHELL_VAR | RO_VAR);
	ft_setenv(shell->env, "EXIT_CODE", temp, SHELL_VAR | RO_VAR);
	free(temp);
	return (exit_shell_code);
}
