/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_fds.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 18:20:05 by lgutter       #+#    #+#                 */
/*   Updated: 2020/06/30 18:20:05 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "environment.h"

int		check_fds(t_shell *shell)
{
	int		ret;
	char	buff;

	ret = 0;
	if (read(STDIN_FILENO, &buff, 0) == -1)
	{
		ret = handle_error_int(bad_fd_error, STDIN_FILENO);
	}
	else if (write(STDOUT_FILENO, "\0", 0) == -1)
	{
		ret = handle_error_int(bad_fd_error, STDOUT_FILENO);
	}
	else if (write(STDERR_FILENO, "\0", 0) == -1)
	{
		ret = d_handle_error_int(STDIN_FILENO, bad_fd_error, STDERR_FILENO);
	}
	if (ret != 0)
	{
		ft_setstatus(shell->env, 1);
		g_error_internal = 0;
		ret = 1;
	}
	return (ret);
}
