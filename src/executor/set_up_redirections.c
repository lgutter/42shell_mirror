/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_up_redirections.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 15:11:54 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/30 15:11:54 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int		set_left_fd(t_redir_info *redir_info, int *left_fd,
							t_io_redirect *redirect)
{
	if (redirect->io_number != NULL && redirect->io_fd >= 0)
		*left_fd = redirect->io_fd;
	else if (redirect->io_file != NULL)
	{
		if (redirect->io_file->redirect_op == redirect_in ||
			redirect->io_file->redirect_op == redirect_fd_in)
			*left_fd = STDIN_FILENO;
		else if (redirect->io_file->redirect_op == redirect_out ||
			redirect->io_file->redirect_op == redirect_append ||
			redirect->io_file->redirect_op == redirect_fd_out)
			*left_fd = STDOUT_FILENO;
		else
			return (d_handle_error(redir_info->std_fds[2], parsing_error));
	}
	else if (redirect->io_here != NULL)
		*left_fd = STDIN_FILENO;
	else
		return (d_handle_error(redir_info->std_fds[2], parsing_error));
	if (add_fd_to_list(dup(*left_fd), *left_fd, redir_info) != 0)
		return (-1);
	return (0);
}

static int		set_up_io_here(t_redir_info *redir_info, int left_fd,
								t_io_redirect *redirect)
{
	int		pipe_fds[2];

	if (redirect->io_here->here_doc == NULL)
	{
		return (d_handle_error_str(redir_info->std_fds[2], parsing_error,
									"NULL heredoc"));
	}
	if (pipe(pipe_fds) != 0)
	{
		return (d_handle_error_str(redir_info->std_fds[2], pipe_failure,
									"while setting up heredoc."));
	}
	if (add_fd_to_list(pipe_fds[0], -1, redir_info) != 0)
		return (-1);
	ft_dprintf(pipe_fds[1], "%s", redirect->io_here->here_doc);
	if (dup2(pipe_fds[0], left_fd) < 0)
	{
		d_handle_error_int(redir_info->std_fds[2], bad_fd_error, left_fd);
		return (-1);
	}
	close(pipe_fds[1]);
	return (0);
}

t_redir_info	*set_up_redirections(t_io_redirect *redirect)
{
	t_redir_info	*redir_info;
	int				left_fd;
	int				ret;

	ret = 0;
	redir_info = (t_redir_info *)ft_memalloc(sizeof(t_redir_info) * 1);
	if (redir_info == NULL)
		return (handle_error_p(malloc_error, NULL));
	std_fd_backup(redir_info->std_fds);
	while (ret == 0 && redirect != NULL)
	{
		if (set_left_fd(redir_info, &left_fd, redirect) != 0)
			ret = -1;
		else if (redirect->io_here != NULL)
			ret = set_up_io_here(redir_info, left_fd, redirect);
		else if (redirect->io_file != NULL)
			ret = set_up_io_file(redir_info, left_fd, redirect->io_file);
		else
			ret = d_handle_error(redir_info->std_fds[2], parsing_error);
		redirect = redirect->next;
	}
	if (ret != 0)
		reset_redirections(&redir_info);
	return (redir_info);
}

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
