/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_fd_to_list.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/01 13:22:19 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/01 13:22:19 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	exception_closed_fd(int fd, t_fd_list *elem)
{
	elem->fd = fd;
	return (0);
}

int			add_fd_to_list(int fd, int og_fd, t_redir_info *red_info)
{
	t_fd_list *temp;
	t_fd_list **target;

	if (red_info == NULL)
		return (-1);
	if (red_info->fd_list == NULL)
		target = &red_info->fd_list;
	else
	{
		temp = red_info->fd_list;
		while (temp->next != NULL && (temp->fd != -2 || temp->og_fd != og_fd))
			temp = temp->next;
		if (temp->og_fd == og_fd && temp->fd == -2)
			return (exception_closed_fd(fd, temp));
		target = &temp->next;
	}
	*target = (t_fd_list *)ft_memalloc(sizeof(t_fd_list) * 1);
	if (*target == NULL)
		return (d_handle_error(red_info->std_fds[2], malloc_error));
	(*target)->fd = fd;
	(*target)->og_fd = og_fd;
	(*target)->next = NULL;
	return (0);
}
