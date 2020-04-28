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
#include "builtins_list.h"

int		is_builtin(char *exec_name)
{
	size_t				i;

	i = 0;
	while (g_builtins[i] != NULL)
	{
		if (ft_strcmp(g_builtins[i], exec_name) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	std_fd_backup(int **old_fds)
{
	if (old_fds != NULL)
	{
		*old_fds = (int *)ft_memalloc(sizeof(int) * 3);
		if (*old_fds != NULL)
		{
			(*old_fds)[0] = dup(STDIN_FILENO);
			(*old_fds)[1] = dup(STDOUT_FILENO);
			(*old_fds)[2] = dup(STDERR_FILENO);
		}
	}
}

void	std_fd_restore(int **old_fds)
{
	if (old_fds != NULL && *old_fds != NULL)
	{
		if ((*old_fds)[0] != -1)
		{
			dup2((*old_fds)[0], STDIN_FILENO);
			close((*old_fds)[0]);
		}
		if ((*old_fds)[1] != -1)
		{
			dup2((*old_fds)[1], STDOUT_FILENO);
			close((*old_fds)[1]);
		}
		if ((*old_fds)[2] != -1)
		{
			dup2((*old_fds)[2], STDERR_FILENO);
			close((*old_fds)[2]);
		}
		free(*old_fds);
		*old_fds = 0;
	}
}
