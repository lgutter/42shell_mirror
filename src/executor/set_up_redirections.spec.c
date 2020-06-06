/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_up_redirections.spec.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/05 14:26:11 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/05 14:26:11 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "executor.h"
#include <string.h>

static void redirect_std_err()
{
	cr_redirect_stderr();
}

Test(set_up_redirections_unit, valid_append_file_once)
{
	t_redir_info	*info = NULL;
	char			*filename = strdup("/tmp/set_up_redirections_unit_valid_append_file_once");
	t_io_file		io_file = {redirect_append, filename};
	t_io_redirect	redirect;
	int				left_fd = 520;
	int				real_fd;
	char			buff[1024];

	remove(filename);
	redirect.io_fd = left_fd;
	redirect.io_number = ft_itoa(left_fd);
	redirect.io_file = &io_file;
	redirect.io_here = NULL;
	redirect.next = NULL;
	memset(buff, 0, 1024);
	info = set_up_redirections(&redirect);
	cr_expect_eq(access(filename, F_OK), 0, "file was not created!");
	cr_expect_eq(access(filename, R_OK), 0, "file does not have read permission!");
	cr_expect_eq(access(filename, W_OK), 0, "file does not have write permission!");
	real_fd = open(filename, O_RDONLY);
	cr_assert_geq(real_fd, 0, "could not open file!");
	cr_assert_eq(0, read(real_fd, buff, 1024), "file is not empty!");
	cr_expect_eq(4, write(left_fd, "test", 4), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(real_fd, buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "expected file content |test|, but got |%s|!", buff);
	remove(filename);
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_not_null(info->fd_list, "fd_list was not created!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
}

Test(set_up_redirections_unit, valid_append_file_twice)
{
	t_redir_info	*info = NULL;
	char			*filename = strdup("/tmp/set_up_redirections_unit_valid_append_file_twice");
	t_io_file		io_file = {redirect_append, filename};
	t_io_redirect	redirect;
	int				left_fd = 521;
	int				real_fd;
	char			buff[1024];

	redirect.io_fd = left_fd;
	redirect.io_number = ft_itoa(left_fd);
	redirect.io_file = &io_file;
	redirect.io_here = NULL;
	redirect.next = NULL;
	memset(buff, 0, 1024);
	info = set_up_redirections(&redirect);
	cr_expect_eq(access(filename, F_OK), 0, "file was not created!");
	cr_expect_eq(access(filename, R_OK), 0, "file does not have read permission!");
	cr_expect_eq(access(filename, W_OK), 0, "file does not have write permission!");
	real_fd = open(filename, O_RDONLY);
	cr_assert_geq(real_fd, 0, "could not open file!");
	cr_assert_eq(0, read(real_fd, buff, 1024), "file is not empty!");
	cr_expect_eq(4, write(left_fd, "test", 4), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(real_fd, buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "expected file content |test|, but got |%s|!", buff);
	close(real_fd);
	real_fd = open(filename, O_RDONLY);
	cr_expect_eq(6, write(left_fd, " again", 6), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(10, read(real_fd, buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test again", "expected file content |test again|, but got |%s|!", buff);
	remove(filename);
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_not_null(info->fd_list, "fd_list was not created!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
}

Test(set_up_redirections_unit, valid_overwrite_file_once)
{
	char			*filename = strdup("/tmp/set_up_redirections_unit_valid_overwrite_file_once");
	t_io_file		io_file = {redirect_out, filename};
	int				left_fd = 522;
	t_io_redirect	redirect;
	t_redir_info	*info = NULL;
	int				real_fd;
	char			buff[1024];

	redirect.io_fd = left_fd;
	redirect.io_number = ft_itoa(left_fd);
	redirect.io_file = &io_file;
	redirect.io_here = NULL;
	redirect.next = NULL;
	memset(buff, 0, 1024);
	info = set_up_redirections(&redirect);
	cr_expect_not_null(info, "unexpected NULL return!");
	cr_expect_eq(access(filename, F_OK), 0, "file was not created!");
	cr_expect_eq(access(filename, R_OK), 0, "file does not have read permission!");
	cr_expect_eq(access(filename, W_OK), 0, "file does not have write permission!");
	real_fd = open(filename, O_RDONLY);
	cr_assert_geq(real_fd, 0, "could not open file!");
	cr_assert_eq(0, read(real_fd, buff, 1024), "file is not empty!");
	cr_expect_eq(4, write(left_fd, "test", 4), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(real_fd, buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "expected file content |test|, but got |%s|!", buff);
	remove(filename);
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_not_null(info->fd_list, "fd_list was not created!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
}

Test(set_up_redirections_unit, valid_overwrite_file_twice)
{
	char			*filename = strdup("/tmp/set_up_redirections_unit_valid_overwrite_file_twice");
	t_io_file		io_file = {redirect_out, filename};
	int				left_fd = 523;
	t_io_redirect	redirect;
	t_redir_info	*info = NULL;
	int				real_fd;
	char			buff[1024];
	int				ret;

	redirect.io_fd = left_fd;
	redirect.io_number = ft_itoa(left_fd);
	redirect.io_file = &io_file;
	redirect.io_here = NULL;
	redirect.next = NULL;
	memset(buff, 0, 1024);
	real_fd = open(filename, O_WRONLY | O_CREAT, 0664);
	cr_assert_geq(real_fd, 0, "could not open file!");
	ret = write(real_fd, "test", 4);
	cr_expect_eq(4, ret, "write went wrong! expected to write 4 bytes, wrote %i bytes!", ret);
	close(real_fd);
	info = set_up_redirections(&redirect);
	cr_expect_eq(access(filename, F_OK), 0, "file was not created!");
	cr_expect_eq(access(filename, R_OK), 0, "file does not have read permission!");
	cr_expect_eq(access(filename, W_OK), 0, "file does not have write permission!");
	real_fd = open(filename, O_RDONLY);
	cr_assert_geq(real_fd, 0, "could not open file!");
	ret = read(real_fd, buff, 1024);
	cr_assert_eq(0, ret, "file content not as expected! expected to read 0 bytes, read %i!", ret);
	close(real_fd);
	real_fd = open(filename, O_RDONLY);
	ret = write(left_fd, " again", 6);
	cr_expect_eq(6, ret, "write went wrong! expected to write 6 bytes, wrote %i bytes!", ret);
	memset(buff, 0, 1024);
	ret = read(real_fd, buff, 1024);
	cr_expect_eq(6, ret, "file content not as expected! expected to read 6 bytes, read %i!", ret);
	cr_expect_str_eq(buff, " again", "expected file content | again|, but got |%s|!", buff);
	remove(filename);
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_not_null(info->fd_list, "fd_list was not created!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
}

Test(set_up_redirections_unit, valid_write_to_fd_no_left_fd)
{
	int				*pipe_fds = (int *)malloc(sizeof(int) * 2);
	char			*filename = NULL;
	t_io_file		io_file;
	int				left_fd = STDOUT_FILENO;
	t_io_redirect	redirect;
	t_redir_info	*info = NULL;
	char			buff[1024];

	redirect.io_fd = -1;
	redirect.io_number = NULL;
	redirect.io_file = &io_file;
	redirect.io_here = NULL;
	redirect.next = NULL;
	memset(buff, 0, 1024);
	cr_assert_eq(pipe(pipe_fds), 0, "pipe failed!");
	filename = ft_itoa(pipe_fds[1]);
	cr_assert_not_null(filename, "fd not correctly copied to filename!");
	io_file.redirect_op = redirect_fd_out;
	io_file.filename = filename;

	info = set_up_redirections(&redirect);
	cr_expect_eq(4, write(left_fd, "test", 4), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(pipe_fds[0], buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "expected file content |test|, but got |%s|!", buff);
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_not_null(info->fd_list, "fd_list was not created!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
}

Test(set_up_redirections_unit, valid_write_to_fd)
{
	int				*pipe_fds = (int *)malloc(sizeof(int) * 2);
	char			*filename = NULL;
	t_io_file		io_file;
	int				left_fd = 524;
	t_io_redirect	redirect;
	t_redir_info	*info = NULL;
	char			buff[1024];

	redirect.io_fd = left_fd;
	redirect.io_number = ft_itoa(left_fd);
	redirect.io_file = &io_file;
	redirect.io_here = NULL;
	redirect.next = NULL;
	memset(buff, 0, 1024);
	cr_assert_eq(pipe(pipe_fds), 0, "pipe failed!");
	filename = ft_itoa(pipe_fds[1]);
	cr_assert_not_null(filename, "fd not correctly copied to filename!");
	io_file.redirect_op = redirect_fd_out;
	io_file.filename = filename;

	info = set_up_redirections(&redirect);
	cr_expect_eq(4, write(left_fd, "test", 4), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(pipe_fds[0], buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "expected file content |test|, but got |%s|!", buff);
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_not_null(info->fd_list, "fd_list was not created!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
}

Test(set_up_redirections_unit, valid_write_to_fd_unclosed_stdout)
{
	int				*pipe_fds = (int *)malloc(sizeof(int) * 2);
	char			*filename = NULL;
	t_io_file		io_file;
	t_io_file		io_file2;
	int				left_fd = STDOUT_FILENO;
	t_io_redirect	redirect;
	t_io_redirect	redirect2;
	t_redir_info	*info = NULL;
	char			buff[1024];

	redirect.io_fd = left_fd;
	redirect.io_number = ft_itoa(left_fd);
	redirect.io_file = &io_file;
	redirect.io_here = NULL;
	redirect.next = &redirect2;
	redirect2.io_fd = left_fd;
	redirect2.io_number = ft_itoa(left_fd);
	redirect2.io_file = &io_file2;
	redirect2.io_here = NULL;
	redirect2.next = NULL;
	io_file.redirect_op = redirect_fd_out;
	io_file.filename = strdup("-");
	memset(buff, 0, 1024);
	cr_assert_eq(pipe(pipe_fds), 0, "pipe failed!");
	filename = ft_itoa(pipe_fds[1]);
	cr_assert_not_null(filename, "fd not correctly copied to filename!");
	io_file2.redirect_op = redirect_fd_out;
	io_file2.filename = filename;

	info = set_up_redirections(&redirect);
	cr_expect_eq(4, write(left_fd, "test", 4), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(pipe_fds[0], buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "expected file content |test|, but got |%s|!", buff);
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
	cr_assert_not_null(info->fd_list, "fd_list was not created!");
	cr_expect_eq(info->fd_list->og_fd, STDOUT_FILENO);
	cr_expect_gt(info->fd_list->fd, 0);
	cr_assert_not_null(info->fd_list->next);
	cr_expect_eq(info->fd_list->next->og_fd, STDOUT_FILENO);
	cr_expect_gt(info->fd_list->next->fd, 0);
	cr_expect_null(info->fd_list->next->next);
}

Test(set_up_redirections_unit, valid_write_to_fd_unclosed_stderr)
{
	int				*pipe_fds = (int *)malloc(sizeof(int) * 2);
	char			*filename = NULL;
	t_io_file		io_file;
	t_io_file		io_file2;
	int				left_fd = STDERR_FILENO;
	t_io_redirect	redirect;
	t_io_redirect	redirect2;
	t_redir_info	*info = NULL;
	char			buff[1024];

	redirect.io_fd = left_fd;
	redirect.io_number = ft_itoa(left_fd);
	redirect.io_file = &io_file;
	redirect.io_here = NULL;
	redirect.next = &redirect2;
	redirect2.io_fd = left_fd;
	redirect2.io_number = ft_itoa(left_fd);
	redirect2.io_file = &io_file2;
	redirect2.io_here = NULL;
	redirect2.next = NULL;
	io_file.redirect_op = redirect_fd_out;
	io_file.filename = strdup("-");
	memset(buff, 0, 1024);
	cr_assert_eq(pipe(pipe_fds), 0, "pipe failed!");
	filename = ft_itoa(pipe_fds[1]);
	cr_assert_not_null(filename, "fd not correctly copied to filename!");
	io_file2.redirect_op = redirect_fd_out;
	io_file2.filename = filename;

	info = set_up_redirections(&redirect);
	cr_expect_eq(4, write(left_fd, "test", 4), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(pipe_fds[0], buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "expected file content |test|, but got |%s|!", buff);
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
	cr_assert_not_null(info->fd_list, "fd_list was not created!");
	cr_expect_eq(info->fd_list->og_fd, STDERR_FILENO);
	cr_expect_gt(info->fd_list->fd, 0);
	cr_assert_not_null(info->fd_list->next);
	cr_expect_eq(info->fd_list->next->og_fd, STDERR_FILENO);
	cr_expect_gt(info->fd_list->next->fd, 0);
	cr_expect_null(info->fd_list->next->next);
}

Test(set_up_redirections_unit, valid_close_fd_stdin)
{
	char			*filename = NULL;
	t_io_file		io_file;
	int				left_fd = STDIN_FILENO;
	t_io_redirect	redirect;
	t_redir_info	*info = NULL;
	char			buff[1024];

	redirect.io_fd = left_fd;
	redirect.io_number = ft_itoa(left_fd);
	redirect.io_file = &io_file;
	redirect.io_here = NULL;
	redirect.next = NULL;
	filename = ft_strdup("-");
	io_file.redirect_op = redirect_fd_out;
	io_file.filename = filename;

	info = set_up_redirections(&redirect);
	memset(buff, 0, 1024);
	cr_expect_eq(-1, read(STDIN_FILENO, buff, 1024), "could read from STDIN, but should be closed!");
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_not_null(info->fd_list, "fd_list was not created!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
	cr_expect_eq(info->fd_list->og_fd, STDIN_FILENO);
	cr_expect_null(info->fd_list->next);
}

Test(set_up_redirections_unit, valid_close_fd_stdout)
{
	char			*filename = NULL;
	t_io_file		io_file;
	int				left_fd = STDOUT_FILENO;
	t_io_redirect	redirect;
	t_redir_info	*info = NULL;
	char			buff[1024];

	redirect.io_fd = left_fd;
	redirect.io_number = ft_itoa(left_fd);
	redirect.io_file = &io_file;
	redirect.io_here = NULL;
	redirect.next = NULL;
	filename = ft_strdup("-");
	io_file.redirect_op = redirect_fd_out;
	io_file.filename = filename;

	info = set_up_redirections(&redirect);
	memset(buff, 0, 1024);
	cr_expect_eq(-1, write(STDOUT_FILENO, "TEST", 4), "could write to STDOUT, but should be closed!");
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_not_null(info->fd_list, "fd_list was not created!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
	cr_expect_eq(info->fd_list->og_fd, STDOUT_FILENO);
	cr_expect_null(info->fd_list->next);
}

Test(set_up_redirections_unit, valid_close_fd_stderr)
{
	char			*filename = NULL;
	t_io_file		io_file;
	int				left_fd = STDERR_FILENO;
	t_io_redirect	redirect;
	t_redir_info	*info = NULL;
	char			buff[1024];

	redirect.io_fd = left_fd;
	redirect.io_number = ft_itoa(left_fd);
	redirect.io_file = &io_file;
	redirect.io_here = NULL;
	redirect.next = NULL;
	filename = ft_strdup("-");
	io_file.redirect_op = redirect_fd_out;
	io_file.filename = filename;

	info = set_up_redirections(&redirect);
	memset(buff, 0, 1024);
	cr_expect_eq(-1, write(STDERR_FILENO, "TEST", 4), "could write to STDERR, but should be closed!");
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_not_null(info->fd_list, "fd_list was not created!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
	cr_expect_eq(info->fd_list->og_fd, STDERR_FILENO);
	cr_expect_null(info->fd_list->next);
}

Test(set_up_redirections_unit, valid_read_from_fd)
{
	int				*pipe_fds = (int *)malloc(sizeof(int) * 2);
	char			*filename = NULL;
	t_io_file		io_file;
	int				left_fd = 525;
	t_io_redirect	redirect;
	t_redir_info	*info = NULL;
	char			buff[1024];

	redirect.io_fd = left_fd;
	redirect.io_number = ft_itoa(left_fd);
	redirect.io_file = &io_file;
	redirect.io_here = NULL;
	redirect.next = NULL;
	memset(buff, 0, 1024);
	cr_assert_eq(pipe(pipe_fds), 0, "pipe failed!");
	filename = ft_itoa(pipe_fds[0]);
	cr_assert_not_null(filename, "fd not correctly copied to filename!");
	io_file.redirect_op = redirect_fd_in;
	io_file.filename = filename;

	info = set_up_redirections(&redirect);
	cr_expect_eq(4, write(pipe_fds[1], "test", 4), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(left_fd, buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "expected file content |test|, but got |%s|!", buff);
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_not_null(info->fd_list, "fd_list was not created!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
}

Test(set_up_redirections_unit, valid_read_from_fd_unclosed_stdin)
{
	int				*pipe_fds = (int *)malloc(sizeof(int) * 2);
	char			*filename = NULL;
	t_io_file		io_file;
	t_io_file		io_file2;
	int				left_fd = STDIN_FILENO;
	t_io_redirect	redirect;
	t_io_redirect	redirect2;
	t_redir_info	*info = NULL;
	char			buff[1024];

	redirect.io_fd = left_fd;
	redirect.io_number = ft_itoa(left_fd);
	redirect.io_file = &io_file;
	redirect.io_here = NULL;
	redirect.next = &redirect2;
	redirect2.io_fd = left_fd;
	redirect2.io_number = ft_itoa(left_fd);
	redirect2.io_file = &io_file2;
	redirect2.io_here = NULL;
	redirect2.next = NULL;
	io_file.redirect_op = redirect_fd_in;
	io_file.filename = strdup("-");
	memset(buff, 0, 1024);
	cr_assert_eq(pipe(pipe_fds), 0, "pipe failed!");
	filename = ft_itoa(pipe_fds[0]);
	cr_assert_not_null(filename, "fd not correctly copied to filename!");
	io_file2.redirect_op = redirect_fd_in;
	io_file2.filename = filename;

	info = set_up_redirections(&redirect);
	cr_expect_eq(4, write(pipe_fds[1], "test", 4), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(left_fd, buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "expected file content |test|, but got |%s|!", buff);
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
	cr_assert_not_null(info->fd_list, "fd_list was not created!");
	cr_expect_eq(info->fd_list->og_fd, STDIN_FILENO);
	cr_expect_gt(info->fd_list->fd, 0);
	cr_assert_not_null(info->fd_list->next);
	cr_expect_eq(info->fd_list->next->og_fd, STDIN_FILENO);
	cr_expect_gt(info->fd_list->next->fd, 0);
	cr_expect_null(info->fd_list->next->next);
}

Test(set_up_redirections_unit, valid_read_from_fd_no_left_fd)
{
	int				*pipe_fds = (int *)malloc(sizeof(int) * 2);
	char			*filename = NULL;
	t_io_file		io_file;
	int				left_fd = STDIN_FILENO;
	t_io_redirect	redirect;
	t_redir_info	*info = NULL;
	char			buff[1024];

	redirect.io_fd = -1;
	redirect.io_number = NULL;
	redirect.io_file = &io_file;
	redirect.io_here = NULL;
	redirect.next = NULL;
	memset(buff, 0, 1024);
	cr_assert_eq(pipe(pipe_fds), 0, "pipe failed!");
	filename = ft_itoa(pipe_fds[0]);
	cr_assert_not_null(filename, "fd not correctly copied to filename!");
	io_file.redirect_op = redirect_fd_in;
	io_file.filename = filename;

	info = set_up_redirections(&redirect);
	cr_expect_eq(4, write(pipe_fds[1], "test", 4), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(left_fd, buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "expected file content |test|, but got |%s|!", buff);
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_not_null(info->fd_list, "fd_list was not created!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
}

Test(set_up_redirections_unit, valid_here_doc)
{
	char			*here_end = strdup("EOF");
	t_io_here		io_here;
	int				left_fd = 526;
	t_io_redirect	redirect;
	t_redir_info	*info = NULL;
	char			buff[1024];

	redirect.io_fd = left_fd;
	redirect.io_number = ft_itoa(left_fd);
	redirect.io_file = NULL;
	redirect.io_here = &io_here;
	redirect.next = NULL;
	memset(buff, 0, 1024);
	io_here.here_end = here_end;
	io_here.here_doc = strdup("test");

	info = set_up_redirections(&redirect);
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(left_fd, buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "expected heredoc content |test|, but got |%s|!", buff);
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_not_null(info->fd_list, "fd_list was not created!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
}

Test(set_up_redirections_unit, valid_here_doc_no_left_fd)
{
	char			*here_end = strdup("EOF");
	t_io_here		io_here;
	int				left_fd = 0;
	t_io_redirect	redirect;
	t_redir_info	*info = NULL;
	char			buff[1024];

	redirect.io_fd = -1;
	redirect.io_number = NULL;
	redirect.io_file = NULL;
	redirect.io_here = &io_here;
	redirect.next = NULL;
	memset(buff, 0, 1024);
	io_here.here_end = here_end;
	io_here.here_doc = strdup("test");

	info = set_up_redirections(&redirect);
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(left_fd, buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "expected heredoc content |test|, but got |%s|!", buff);
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_not_null(info->fd_list, "fd_list was not created!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
}

Test(set_up_redirections_unit, valid_here_doc_append_file_once)
{
	char			*filename = strdup("/tmp/set_up_redirections_unit_valid_here_doc_append_file_once");
	t_io_file		io_file = {redirect_append, filename};
	t_io_here		io_here;
	char			*here_end = strdup("EOF");
	int				left_fd_here = 528;
	int				left_fd_file = 529;
	t_io_redirect	redirect;
	t_io_redirect	redirect1;
	t_redir_info	*info = NULL;
	char			buff[1024];
	int				real_fd;

	redirect.io_fd = left_fd_here;
	redirect.io_number = ft_itoa(left_fd_here);
	redirect.io_file = NULL;
	redirect.io_here = &io_here;
	redirect.next = &redirect1;
	redirect1.io_fd = left_fd_file;
	redirect1.io_number = ft_itoa(left_fd_file);
	redirect1.io_file = &io_file;
	redirect1.io_here = NULL;
	redirect1.next = NULL;
	memset(buff, 0, 1024);
	io_here.here_end = here_end;
	io_here.here_doc = strdup("test");

	info = set_up_redirections(&redirect);
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(left_fd_here, buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "expected heredoc content |test|, but got |%s|!", buff);

	cr_expect_eq(access(filename, F_OK), 0, "file was not created!");
	cr_expect_eq(access(filename, R_OK), 0, "file does not have read permission!");
	cr_expect_eq(access(filename, W_OK), 0, "file does not have write permission!");
	real_fd = open(filename, O_RDONLY);
	cr_assert_geq(real_fd, 0, "could not open file!");
	cr_assert_eq(0, read(real_fd, buff, 1024), "file is not empty!");
	cr_expect_eq(4, write(left_fd_file, "test", 4), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(real_fd, buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "expected file content |test|, but got |%s|!", buff);
	remove(filename);
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_not_null(info->fd_list, "fd_list was not created!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
}

Test(set_up_redirections_unit, invalid_here_doc_no_here_doc, .init = redirect_std_err)
{
	char			*here_end = strdup("EOF");
	t_io_here		io_here;
	int				left_fd = 527;
	t_io_redirect	redirect;
	t_redir_info	*info = NULL;

	redirect.io_fd = left_fd;
	redirect.io_number = ft_itoa(left_fd);
	redirect.io_file = NULL;
	redirect.io_here = &io_here;
	redirect.next = NULL;
	io_here.here_end = here_end;
	io_here.here_doc = NULL;

	info = set_up_redirections(&redirect);
	cr_expect_null(info, "unexpected non-NULL return!");
	fflush(stderr);
	cr_expect_stderr_eq_str("Parsing error detected: NULL heredoc\n");
}

Test(set_up_redirections_unit, invalid_NULL_redirect)
{
	t_redir_info	*info = NULL;

	info = set_up_redirections(NULL);
	cr_assert_not_null(info, "unexpected NULL return!");
	cr_expect_null(info->fd_list, "fd_list is not NULL, but should be NULL!");
	cr_expect_not_null(info->std_fds, "std_fds was not prepared!");
}

Test(set_up_redirections_unit, invalid_empty_redirect, .init = redirect_std_err)
{
	t_redir_info	*info = NULL;
	t_io_redirect	redirect = {NULL, -1, NULL, NULL, NULL};

	info = set_up_redirections(&redirect);
	cr_expect_null(info, "unexpected NULL return!");
	fflush(stderr);
	cr_expect_stderr_eq_str("Parsing error detected\n");
}

Test(reset_redirections_unit, valid_close_single_fd)
{
	int ret;
	t_redir_info	*info = malloc(sizeof(t_redir_info) * 1);
	info->fd_list = malloc(sizeof(t_fd_list) * 1);
	info->std_fds[0] = 0;
	info->std_fds[1] = 1;
	info->std_fds[2] = 2;
	int	newfd = dup(1);
	info->fd_list->fd = newfd;
	info->fd_list->og_fd = -1;
	info->fd_list->next = NULL;
	int testfd = dup(newfd);
	cr_assert_geq(testfd, 0, "could not dup fd before resetting!");
	close(testfd);
	ret = reset_redirections(&info);
	cr_expect_null(info);
	testfd = dup(newfd);
	cr_expect_lt(testfd, 0, "fd was not closed by reset_redirections!");
	cr_expect_eq(ret, 0);
}

Test(reset_redirections_unit, valid_close_fd_restore_fd)
{
	int ret;
	t_redir_info	*info = malloc(sizeof(t_redir_info) * 1);
	t_fd_list	*list2 = malloc(sizeof(t_fd_list) * 1);
	info->fd_list = malloc(sizeof(t_fd_list) * 1);
	info->std_fds[0] = 0;
	info->std_fds[1] = 1;
	info->std_fds[2] = 2;
	int	closefd = dup(1);
	info->fd_list->fd = closefd;
	info->fd_list->og_fd = -1;
	info->fd_list->next = list2;
	int testfd = dup(closefd);
	cr_assert_geq(testfd, 0, "could not dup fd before resetting!");
	close(testfd);

	int	restorefd = dup(1);
	testfd = dup(restorefd);
	cr_assert_geq(testfd, 0, "could not dup fd before resetting!");
	list2->fd = testfd;
	list2->og_fd = restorefd;
	list2->next = NULL;
	close(restorefd);
	testfd = dup(restorefd);
	cr_assert_lt(testfd, 0, "could dup fd before resetting, even though is should be closed!");
	ret = reset_redirections(&info);
	cr_expect_null(info);
	testfd = dup(closefd);
	cr_expect_lt(testfd, 0, "fd was not closed by reset_redirections!");
	close(testfd);
	testfd = dup(restorefd);
	cr_expect_geq(testfd, 0, "fd was not restored by reset_redirections!");
	cr_expect_eq(ret, 0);
}

Test(reset_redirections_unit, invalid_NULL_fd_list)
{
	int ret;
	t_redir_info	*info = malloc(sizeof(t_redir_info) * 1);
	info->fd_list = NULL;
	info->std_fds[0] = 0;
	info->std_fds[1] = 1;
	info->std_fds[2] = 2;
	ret = reset_redirections(&info);
	cr_expect_null(info);
	cr_expect_eq(ret, 0);
}

Test(reset_redirections_unit, invalid_NULL_std_fds)
{
	int ret;
	t_redir_info	*info = malloc(sizeof(t_redir_info) * 1);
	info->fd_list = malloc(sizeof(t_fd_list) * 1);
	int	newfd = dup(1);
	info->fd_list->fd = newfd;
	info->fd_list->og_fd = -1;
	info->fd_list->next = NULL;
	int testfd = dup(newfd);
	cr_assert_geq(testfd, 0, "could not dup fd before resetting!");
	close(testfd);
	ret = reset_redirections(&info);
	cr_expect_eq(ret, 0);
	cr_expect_null(info);
	testfd = dup(newfd);
	cr_expect_lt(testfd, 0, "fd was not closed by reset_redirections!");
}

Test(reset_redirections_unit, invalid_NULL_info)
{
	int ret;
	t_redir_info	*info = NULL;
	ret = reset_redirections(&info);
	cr_expect_null(info);
	cr_expect_eq(ret, -1);
}

Test(reset_redirections_unit, invalid_NULL_info_pointer)
{
	int ret;
	ret = reset_redirections(NULL);
	cr_expect_eq(ret, -1);
}
