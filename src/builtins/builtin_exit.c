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

static int	exit_error_check(t_shell *shell, char **argv)
{
	if (shell->job_control != NULL && shell->job_control->job_list != NULL)
	{
		ft_dprintf(STDERR_FILENO, "Cetushell: you have unfinished jobs.\n");
		return (1);
	}
	else if (argv != NULL && ft_str_arr_len(argv) > 2)
	{
		handle_prefix_error(too_many_arguments, "exit");
		return (1);
	}
	else if (argv != NULL && ft_str_arr_len(argv) == 2)
	{
		if (ft_isdigit(argv[1][0]) != true &&
										argv[1][0] != '-' && argv[1][0] != '+')
		{
			handle_prefix_error_str(num_arg_required, "exit", argv[1]);
			return (2);
		}
	}
	return (0);
}

int			builtin_exit(t_shell *shell, char **argv)
{
	char	*temp;
	int		ret;

	if (shell == NULL)
		return (exit_shell_code);
	ret = exit_error_check(shell, argv);
	if (ret == 1)
		return (ret);
	temp = ft_getenv(shell->env, "?", SHELL_VAR);
	if (shell->interactive == true)
		configure_terminal(NULL, 0);
	if (ret == 0 && argv != NULL && argv[0] != NULL && argv[1] != NULL)
		ret = ft_atoi(argv[1]);
	else if (ret == 0)
		ret = (temp == NULL) ? 0 : ft_atoi(temp);
	free(temp);
	temp = ft_itoa(ret);
	if (temp == NULL)
		ft_setenv(shell->env, "EXIT_CODE", "1", SHELL_VAR | RO_VAR);
	ft_setenv(shell->env, "EXIT_CODE", temp, SHELL_VAR | RO_VAR);
	free(temp);
	return (exit_shell_code);
}
