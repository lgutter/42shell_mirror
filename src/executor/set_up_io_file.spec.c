/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_up_io_file.spec.c                              :+:    :+:            */
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

Test(set_up_io_file_unit, valid_append_file_once)
{
	t_redir_info	info = {NULL, NULL};
	char			*filename = strdup("/tmp/set_up_io_file_unit_valid_append_file_once");
	t_io_file		io_file = {redirect_append, filename};
	int				ret;
	int				exp_ret = 0;
	int				left_fd = 420;
	int				real_fd;
	char			buff[1024];

	info.std_fds = (int *)malloc(sizeof(int) * 3);
	info.std_fds[0] = 0;
	info.std_fds[1] = 1;
	info.std_fds[2] = 2;
	memset(buff, 0, 1024);
	ret = set_up_io_file(&info, left_fd, &io_file);
	cr_expect_eq(ret, 0, "expected ret %i, got %i!", exp_ret, ret);
	cr_expect_not_null(info.fd_list);
	cr_expect_not_null(info.std_fds);
	cr_expect_eq(access(filename, F_OK), 0, "file was not created!");
	cr_expect_eq(access(filename, R_OK), 0, "file does not have read permission!");
	cr_expect_eq(access(filename, W_OK), 0, "file does not have write permission!");
	real_fd = open(filename, O_RDONLY);
	cr_assert_geq(real_fd, 0, "could not open file!");
	cr_assert_eq(0, read(real_fd, buff, 1024), "file is not empty!");
	cr_expect_eq(4, write(left_fd, "test", 4), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(real_fd, buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "unexpected file content!");
	remove(filename);
}

Test(set_up_io_file_unit, valid_append_file_twice)
{
	t_redir_info	info = {NULL, NULL};
	char			*filename = strdup("/tmp/set_up_io_file_unit_valid_append_file_twice");
	t_io_file		io_file = {redirect_append, filename};
	int				ret;
	int				exp_ret = 0;
	int				left_fd = 421;
	int				real_fd;
	char			buff[1024];

	info.std_fds = (int *)malloc(sizeof(int) * 3);
	info.std_fds[0] = 0;
	info.std_fds[1] = 1;
	info.std_fds[2] = 2;
	memset(buff, 0, 1024);
	ret = set_up_io_file(&info, left_fd, &io_file);
	cr_expect_eq(ret, 0, "expected ret %i, got %i!", exp_ret, ret);
	cr_expect_not_null(info.fd_list);
	cr_expect_not_null(info.std_fds);
	cr_expect_eq(access(filename, F_OK), 0, "file was not created!");
	cr_expect_eq(access(filename, R_OK), 0, "file does not have read permission!");
	cr_expect_eq(access(filename, W_OK), 0, "file does not have write permission!");
	real_fd = open(filename, O_RDONLY);
	cr_assert_geq(real_fd, 0, "could not open file!");
	cr_assert_eq(0, read(real_fd, buff, 1024), "file is not empty!");
	cr_expect_eq(4, write(left_fd, "test", 4), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(real_fd, buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "unexpected file content!");
	close(real_fd);
	real_fd = open(filename, O_RDONLY);
	cr_expect_eq(6, write(left_fd, " again", 6), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(10, read(real_fd, buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test again", "unexpected file content!");
	remove(filename);
}

Test(set_up_io_file_unit, valid_overwrite_file_once)
{
	t_redir_info	info = {NULL, NULL};
	char			*filename = strdup("/tmp/set_up_io_file_unit_valid_overwrite_file_once");
	t_io_file		io_file = {redirect_out, filename};
	int				ret;
	int				exp_ret = 0;
	int				left_fd = 422;
	int				real_fd;
	char			buff[1024];

	info.std_fds = (int *)malloc(sizeof(int) * 3);
	info.std_fds[0] = 0;
	info.std_fds[1] = 1;
	info.std_fds[2] = 2;
	memset(buff, 0, 1024);
	ret = set_up_io_file(&info, left_fd, &io_file);
	cr_expect_eq(ret, 0, "expected ret %i, got %i!", exp_ret, ret);
	cr_expect_not_null(info.fd_list);
	cr_expect_not_null(info.std_fds);
	cr_expect_eq(access(filename, F_OK), 0, "file was not created!");
	cr_expect_eq(access(filename, R_OK), 0, "file does not have read permission!");
	cr_expect_eq(access(filename, W_OK), 0, "file does not have write permission!");
	real_fd = open(filename, O_RDONLY);
	cr_assert_geq(real_fd, 0, "could not open file!");
	cr_assert_eq(0, read(real_fd, buff, 1024), "file is not empty!");
	cr_expect_eq(4, write(left_fd, "test", 4), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(real_fd, buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "unexpected file content!");
	remove(filename);
}

Test(set_up_io_file_unit, valid_overwrite_file_twice)
{
	t_redir_info	info = {NULL, NULL};
	char			*filename = strdup("/tmp/set_up_io_file_unit_valid_overwrite_file_twice");
	t_io_file		io_file = {redirect_out, filename};
	int				ret;
	int				exp_ret = 0;
	int				left_fd = 423;
	int				real_fd;
	char			buff[1024];

	info.std_fds = (int *)malloc(sizeof(int) * 3);
	info.std_fds[0] = 0;
	info.std_fds[1] = 1;
	info.std_fds[2] = 2;
	memset(buff, 0, 1024);
	real_fd = open(filename, O_WRONLY | O_CREAT, 0664);
	cr_assert_geq(real_fd, 0, "could not open file!");
	ret = write(real_fd, "test", 4);
	cr_expect_eq(4, ret, "write went wrong! expected to write 4 bytes, wrote %i bytes!", ret);
	close(real_fd);
	ret = set_up_io_file(&info, left_fd, &io_file);
	cr_expect_eq(ret, 0, "expected ret %i, got %i!", exp_ret, ret);
	cr_expect_not_null(info.fd_list);
	cr_expect_not_null(info.std_fds);
	cr_expect_eq(access(filename, F_OK), 0, "file was not created!");
	cr_expect_eq(access(filename, R_OK), 0, "file does not have read permission!");
	cr_expect_eq(access(filename, W_OK), 0, "file does not have write permission!");
	real_fd = open(filename, O_RDONLY);
	cr_assert_geq(real_fd, 0, "could not open file!");
	ret = read(real_fd, buff, 1024);
	cr_assert_eq(4, ret, "file content not as expected! expected to read 4 bytes, read %i!", ret);
	close(real_fd);
	real_fd = open(filename, O_RDONLY);
	ret = write(left_fd, " again", 6);
	cr_expect_eq(6, ret, "write went wrong! expected to write 6 bytes, wrote %i bytes!", ret);
	memset(buff, 0, 1024);
	ret = read(real_fd, buff, 1024);
	cr_expect_eq(6, ret, "file content not as expected! expected to read 6 bytes, read %i!", ret);
	cr_expect_str_eq(buff, " again", "unexpected file content!");
	remove(filename);
}

Test(set_up_io_file_unit, valid_write_to_fd)
{
	t_redir_info	info = {NULL, NULL};
	int				*pipe_fds = (int *)malloc(sizeof(int) * 2);
	char			*filename = NULL;
	t_io_file		io_file;
	int				ret;
	int				exp_ret = 0;
	int				left_fd = 424;
	char			buff[1024];

	info.std_fds = (int *)malloc(sizeof(int) * 3);
	info.std_fds[0] = 0;
	info.std_fds[1] = 1;
	info.std_fds[2] = 2;
	cr_assert_eq(pipe(pipe_fds), 0, "pipe failed!");
	filename = ft_itoa(pipe_fds[1]);
	cr_assert_not_null(filename, "fd not correctly copied to filename!");
	io_file.redirect_op = redirect_fd_out;
	io_file.filename = filename;

	ret = set_up_io_file(&info, left_fd, &io_file);
	cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
	cr_expect_null(info.fd_list);
	cr_expect_not_null(info.std_fds);
	cr_expect_eq(4, write(left_fd, "test", 4), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(pipe_fds[0], buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "unexpected file content!");
}

Test(set_up_io_file_unit, valid_read_from_fd)
{
	t_redir_info	info = {NULL, NULL};
	int				*pipe_fds = (int *)malloc(sizeof(int) * 2);
	char			*filename = NULL;
	t_io_file		io_file;
	int				ret;
	int				exp_ret = 0;
	int				left_fd = 425;
	char			buff[1024];

	info.std_fds = (int *)malloc(sizeof(int) * 3);
	info.std_fds[0] = 0;
	info.std_fds[1] = 1;
	info.std_fds[2] = 2;
	cr_assert_eq(pipe(pipe_fds), 0, "pipe failed!");
	filename = ft_itoa(pipe_fds[0]);
	cr_assert_not_null(filename, "fd not correctly copied to filename!");
	io_file.redirect_op = redirect_fd_in;
	io_file.filename = filename;

	ret = set_up_io_file(&info, left_fd, &io_file);
	cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
	cr_expect_null(info.fd_list);
	cr_expect_not_null(info.std_fds);
	cr_expect_eq(4, write(pipe_fds[1], "test", 4), "write went wrong!");
	memset(buff, 0, 1024);
	cr_expect_eq(4, read(left_fd, buff, 1024), "incorrect number of bytes read");
	cr_expect_str_eq(buff, "test", "unexpected file content!");
}

Test(set_up_io_file_unit, invalid_NULL_info)
{
	char			*filename = strdup("foo");
	t_io_file		io_file;
	int				ret;
	int				exp_ret = -1;
	int				left_fd = 426;

	io_file.redirect_op = redirect_fd_in;
	io_file.filename = filename;

	ret = set_up_io_file(NULL, left_fd, &io_file);
	cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
}

Test(set_up_io_file_unit, invalid_NULL_std_fds)
{
	t_redir_info	info = {NULL, NULL};
	char			*filename = strdup("foo");
	t_io_file		io_file;
	int				ret;
	int				exp_ret = -1;
	int				left_fd = 427;

	io_file.redirect_op = redirect_fd_in;
	io_file.filename = filename;

	ret = set_up_io_file(&info, left_fd, &io_file);
	cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
}

Test(set_up_io_file_unit, invalid_NULL_filename, .init = redirect_std_err)
{
	t_redir_info	info = {NULL, NULL};
	char			*filename = NULL;
	t_io_file		io_file;
	int				ret;
	int				exp_ret = -1;
	int				left_fd = 428;

	info.std_fds = (int *)malloc(sizeof(int) * 3);
	info.std_fds[0] = 0;
	info.std_fds[1] = 1;
	info.std_fds[2] = 2;
	io_file.redirect_op = redirect_fd_in;
	io_file.filename = filename;

	ret = set_up_io_file(&info, left_fd, &io_file);
	cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
	fflush(stderr);
	cr_expect_stderr_eq_str("Parsing error detected\n");
}

Test(set_up_io_file_unit, invalid_NULL_io_file, .init = redirect_std_err)
{
	t_redir_info	info = {NULL, NULL};
	int				ret;
	int				exp_ret = -1;
	int				left_fd = 429;

	info.std_fds = (int *)malloc(sizeof(int) * 3);
	info.std_fds[0] = 0;
	info.std_fds[1] = 1;
	info.std_fds[2] = 2;

	ret = set_up_io_file(&info, left_fd, NULL);
	cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
	fflush(stderr);
	cr_expect_stderr_eq_str("Parsing error detected\n");
}
