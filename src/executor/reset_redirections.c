/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset_redirections.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 12:29:21 by lgutter       #+#    #+#                 */
/*   Updated: 2020/06/06 12:29:21 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int				reset_redirections(t_redir_info **redir_info)
{
	t_fd_list	*current;
	t_fd_list	*temp;

	if (redir_info == NULL || (*redir_info) == NULL)
		return (-1);
	std_fd_restore((*redir_info)->std_fds);
	current = (*redir_info)->fd_list;
	while (current != NULL)
	{
		temp = current;
		if (current->og_fd >= 0 && current->fd >= 0)
			if (dup2(current->fd, current->og_fd) < 0)
				d_handle_error_int((*redir_info)->std_fds[2],
									restore_fd_fail, current->og_fd);
		if (current->fd < 0 && current->og_fd >= 0)
			close(current->og_fd);
		close(current->fd);
		current = current->next;
		temp->next = NULL;
		free(temp);
	}
	(*redir_info)->fd_list = NULL;
	free(*redir_info);
	*redir_info = NULL;
	return (0);
}
