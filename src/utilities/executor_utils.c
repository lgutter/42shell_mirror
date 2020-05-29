/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:07:24 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/29 16:07:24 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "builtins.h"

void	std_fd_backup(int old[3])
{
	if (old != NULL)
	{
		(old)[0] = dup(STDIN_FILENO);
		(old)[1] = dup(STDOUT_FILENO);
		(old)[2] = dup(STDERR_FILENO);
	}
}

void	std_fd_restore(int old[3])
{
	if (old != NULL)
	{
		if ((old)[0] != -1)
		{
			if (dup2((old)[0], STDIN_FILENO) < 0)
				d_handle_error_int((old)[2], restore_fd_fail, STDIN_FILENO);
			close((old)[0]);
		}
		if ((old)[1] != -1)
		{
			if (dup2((old)[1], STDOUT_FILENO) < 0)
				d_handle_error_int((old)[2], restore_fd_fail, STDOUT_FILENO);
			close((old)[1]);
		}
		if ((old)[2] != -1)
		{
			if (dup2((old)[2], STDERR_FILENO) < 0)
				d_handle_error_int((old)[2], restore_fd_fail, STDERR_FILENO);
			close((old)[2]);
		}
		old = 0;
	}
}
