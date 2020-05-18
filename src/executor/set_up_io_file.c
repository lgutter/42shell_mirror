/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_up_io_file.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/04 10:52:45 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/04 10:52:45 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int		set_file_out(t_redir_info *redir_info, t_io_file *io_file)
{
	int fd;

	fd = -1;
	if (access(io_file->filename, F_OK) == 0 &&
		access(io_file->filename, W_OK) != 0)
	{
		d_handle_error_str(redir_info->std_fds[2],
							access_denied, io_file->filename);
	}
	else if (io_file->redirect_op == redirect_append)
		fd = open(io_file->filename, O_WRONLY | O_APPEND | O_CREAT, 0664);
	else if (io_file->redirect_op == redirect_out)
		fd = open(io_file->filename, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (fd >= 0)
		add_fd_to_list(fd, -1, redir_info);
	return (fd);
}

static int		set_file_fd(t_redir_info *redir_info, t_io_file *io_file)
{
	int fd;

	fd = -1;
	if (io_file->redirect_op == redirect_append ||
			io_file->redirect_op == redirect_out)
		fd = set_file_out(redir_info, io_file);
	else if (io_file->redirect_op == redirect_in)
	{
		if (access(io_file->filename, F_OK) != 0)
			d_handle_error_str(redir_info->std_fds[2],
					no_such_file_or_dir, io_file->filename);
		else if (access(io_file->filename, R_OK) != 0)
			d_handle_error_str(redir_info->std_fds[2],
					access_denied, io_file->filename);
		else
			fd = open(io_file->filename, O_RDONLY);
		if (fd >= 0)
			add_fd_to_list(fd, -1, redir_info);
	}
	else
		fd = ft_atoi(io_file->filename);
	return (fd);
}

int				set_up_io_file(t_redir_info *redir_info, int left_fd,
								t_io_file *io_file)
{
	int fd;

	if (redir_info == NULL || io_file == NULL || io_file->filename == NULL)
		return (-1);
	if (io_file->filename[0] == '-' && io_file->filename[1] == '\0')
		return (close(left_fd));
	fd = set_file_fd(redir_info, io_file);
	if (fd < 0)
		return (-1);
	if (dup2(fd, left_fd) < 0)
	{
		d_handle_error_int(redir_info->std_fds[2], bad_fd_error, fd);
		return (-1);
	}
	return (0);
}
