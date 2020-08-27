/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/05/07 23:10:37 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool		echo_write_error(bool no_newline, char **argv)
{
	if (no_newline == false || ft_str_arr_len(argv) > 2)
	{
		if (write(STDOUT_FILENO, "", 0) == -1)
		{
			handle_prefix_error_str(bad_fd_error, "echo", "write error");
			return (true);
		}
	}
	return (false);
}

int				builtin_echo(t_shell *shell, char **argv)
{
	int i;
	bool no_newline;

	(void)shell;
	no_newline = false;
	if (argv == NULL || argv[0] == NULL)
		return (-1);
	i = 1;
	if (ft_str_arr_len(argv) > 1 && ft_strcmp(argv[1], "-n") == 0)
	{
		no_newline = true;
		i++;
	}
	if (echo_write_error(no_newline, argv) == true)
		return (1);
	while (i < (int)ft_str_arr_len(argv) && argv[i] != NULL)
	{
		ft_printf("%s", argv[i]);
		if (i < (int)ft_str_arr_len(argv) - 1)
			ft_printf(" ");
		i++;
	}
	if (no_newline == false)
		ft_printf("\n");
	return (0);
}
