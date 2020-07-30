/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_test.spec.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/30 12:46:54 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/30 12:46:54 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/un.h>
#include <sys/socket.h>

#include "builtins.h"
#include "test_expressions.h"
#include "error_str.h"

// int			builtin_test(t_shell *shell, char **argv);

Test(built_test_unit, error_unmatched_bracket, .init = cr_redirect_stderr)
{
	char	*input = "[ -z foo";
	int		expected_ret = 2;
	char	*expected_error = "Cetushell: [: ']' expected\n";


	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	int ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
	fflush(stderr);
	cr_expect_stderr_eq_str(expected_error);
}

Test(built_test_unit, error_too_many_args, .init = cr_redirect_stderr)
{
	char	*input = "test -z foo bar baz";
	int		expected_ret = 2;
	char	expected_error[1024];


	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	int ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
	snprintf(expected_error, 1024, "Cetushell: %s: %s\n", argv[0], g_error_str[too_many_arguments]);
	fflush(stderr);
	cr_expect_stderr_eq_str(expected_error);
}

Test(built_test_unit, error_invalid_unary_op_other_op, .init = cr_redirect_stderr)
{
	char	*input = "[ -eq foo ]";
	int		expected_ret = 2;
	char	expected_error[1024];


	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	int ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
	snprintf(expected_error, 1024, "Cetushell: %s: %s: unary operator expected\n", argv[0], argv[1]);
	fflush(stderr);
	cr_expect_stderr_eq_str(expected_error);
}

Test(built_test_unit, error_invalid_unary_op_not_op, .init = cr_redirect_stderr)
{
	char	*input = "[ foo foo ]";
	int		expected_ret = 2;
	char	expected_error[1024];


	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	int ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
	snprintf(expected_error, 1024, "Cetushell: %s: %s: unary operator expected\n", argv[0], argv[1]);
	fflush(stderr);
	cr_expect_stderr_eq_str(expected_error);
}

Test(built_test_unit, valid_single_arg_true)
{
	char	*input = "test foo";
	int		expected_ret = 0;


	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	int ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
}

Test(built_test_unit, valid_single_arg_true_negate)
{
	char	*input = "test ! foo";
	int		expected_ret = 1;


	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	int ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
}

Test(built_test_unit, valid_single_arg_false)
{
	char	*input = "test";
	int		expected_ret = 1;


	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	int ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
}

Test(built_test_unit, valid_single_arg_false_negate)
{
	char	*input = "test !";
	int		expected_ret = 0;


	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	int ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
}

Test(built_test_unit, valid_unary_non_zero_str_true)
{
	char	*input = "[ -n foo ]";
	int		expected_ret = 0;


	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	int ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
}

Test(built_test_unit, valid_unary_non_zero_str_true_negate)
{
	char	*input = "[ ! -n foo ]";
	int		expected_ret = 1;


	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	int ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
}

Test(built_test_unit, valid_unary_non_zero_str_false)
{
	char	*input = "[ -z foo ]";
	int		expected_ret = 1;


	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	int ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
}

Test(built_test_unit, valid_unary_zero_str_false_negate)
{
	char	*input = "[ ! -z foo ]";
	int		expected_ret = 0;


	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	int ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
}

Test(built_test_unit, valid_regular_file_exists_a)
{
	char	*filename = "/tmp/valid_regular_file_exists_a";
	char	*input = "[ -a /tmp/valid_regular_file_exists_a ]";
	int		expected_ret = 0;

	remove(filename);
	int ret = open(filename, (O_CREAT | O_RDWR), 0664);
	if (ret < 0)
		perror("open");
	cr_assert_geq(ret, 0, "open failed! ret is %i", ret);
	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
	remove(filename);
}

Test(built_test_unit, valid_regular_file)
{
	char	*filename = "/tmp/valid_regular_file";
	char	*input = "[ -f /tmp/valid_regular_file ]";
	int		expected_ret = 0;

	remove(filename);
	int ret = open(filename, (O_CREAT | O_RDWR), 0664);
	if (ret < 0)
		perror("open");
	cr_assert_geq(ret, 0, "open failed! ret is %i", ret);
	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
	remove(filename);
}

Test(built_test_unit, valid_regular_file_exists_e_negate)
{
	char	*filename = "/tmp/valid_regular_file_exists_e";
	char	*input = "[ ! -e /tmp/valid_regular_file_exists_e ]";
	int		expected_ret = 1;

	remove(filename);
	int ret = open(filename, (O_CREAT | O_RDWR), 0664);
	if (ret < 0)
		perror("open");
	cr_assert_geq(ret, 0, "open failed! ret is %i", ret);
	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
	remove(filename);
}

Test(built_test_unit, valid_block_file_exists)
{
	if (getenv("CI_ENVIRONMENT") != NULL)
		cr_skip("no block files in CI environment, so test diabled!");
	char	*input = "[ -b /dev/loop0 ]";
	int		expected_ret = 0;

	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	int ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
}

Test(built_test_unit, valid_char_file_exists)
{
	char	*input = "[ -c /dev/null ]";
	int		expected_ret = 0;

	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	int ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
}

Test(built_test_unit, valid_dir_exists_negate)
{
	char	*input = "test ! -d /dev";
	int		expected_ret = 1;

	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	int ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
}

Test(built_test_unit, valid_group_id_set)
{
	char	*filename = "/tmp/valid_group_id_set";
	char	*input = "[ -g /tmp/valid_group_id_set ]";
	int		expected_ret = 0;

	remove(filename);
	int ret = open(filename, (O_CREAT | O_RDWR), 02664);
	if (ret < 0)
		perror("open");

	cr_assert_geq(ret, 0, "open failed! ret is %i", ret);
	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
	remove(filename);
}

Test(built_test_unit, valid_user_id_set_negate)
{
	char	*filename = "/tmp/valid_user_id_set";
	char	*input = "test ! -u /tmp/valid_user_id_set";
	int		expected_ret = 1;

	remove(filename);
	int ret = open(filename, (O_CREAT | O_RDWR), 04664);
	if (ret < 0)
		perror("open");
	cr_assert_geq(ret, 0, "open failed! ret is %i", ret);
	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
	remove(filename);
}

Test(built_test_unit, valid_read_permission_negate)
{
	char	*filename = "/tmp/valid_read_permissions";
	char	*input = "test ! -r /tmp/valid_read_permissions";
	int		expected_ret = 1;

	remove(filename);
	int ret = open(filename, (O_CREAT | O_RDWR), 0444);
	if (ret < 0)
		perror("open");
	cr_assert_geq(ret, 0, "open failed! ret is %i", ret);
	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
	remove(filename);
}

Test(built_test_unit, valid_write_permission)
{
	char	*filename = "/tmp/valid_write_permissions";
	char	*input = "[ -w /tmp/valid_write_permissions ]";
	int		expected_ret = 0;

	remove(filename);
	int ret = open(filename, (O_CREAT | O_RDWR), 0222);
	if (ret < 0)
		perror("open");
	cr_assert_geq(ret, 0, "open failed! ret is %i", ret);
	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
	remove(filename);
}

Test(built_test_unit, valid_exec_permission)
{
	char	*filename = "/tmp/valid_execute_permissions";
	char	*input = "[ -x /tmp/valid_execute_permissions ]";
	int		expected_ret = 0;

	remove(filename);
	int ret = open(filename, (O_CREAT | O_RDWR), 0111);
	if (ret < 0)
		perror("open");
	cr_assert_geq(ret, 0, "open failed! ret is %i", ret);
	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
	remove(filename);
}

Test(built_test_unit, valid_fifo_file)
{
	char	*filename = "/tmp/valid_fifo_file";
	char	*input = "[ -p /tmp/valid_fifo_file ]";
	int		expected_ret = 0;

	remove(filename);
	int ret = mkfifo(filename, 0111);
	if (ret < 0)
		perror("mkfifo");
	cr_assert_geq(ret, 0, "mkfifo failed! ret is %i", ret);
	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
	remove(filename);
}

Test(built_test_unit, valid_non_zero_file_size_negate)
{
	char	*filename = "/tmp/valid_non_zero_file_size";
	char	*input = "[ ! -s /tmp/valid_non_zero_file_size ]";
	int		expected_ret = 0;

	remove(filename);
	int ret = open(filename, (O_CREAT | O_RDWR), 0666);
	if (ret < 0)
		perror("open");
	cr_assert_geq(ret, 0, "open failed! ret is %i", ret);
	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
	remove(filename);
}

Test(built_test_unit, valid_socket_file)
{
	char	*filename = "/tmp/valid_socket_file";
	char	*input = "[ -S /tmp/valid_socket_file ]";
	int		expected_ret = 0;

	remove(filename);
	struct sockaddr_un namesock;
    int fd;
    namesock.sun_family = AF_UNIX;
    strncpy(namesock.sun_path, (char *)filename, sizeof(namesock.sun_path));
    fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    bind(fd, (struct sockaddr *) &namesock, sizeof(struct sockaddr_un));
    close(fd);
	char **argv = ft_strsplit(input, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	int ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
	remove(filename);
}



Test(built_test_unit, valid_symlink_combination)
{
	char	*filename = "/tmp/valid_symlink";
	char	*linkname = "/tmp/link_to_valid_symlink";
	char	*input1 = "test ! -L /tmp/link_to_valid_symlink";
	char	*input2 = "test -h /tmp/link_to_valid_symlink";
	int		expected_ret = 1;

	remove(filename);
	remove(linkname);
	int ret = open(filename, (O_CREAT | O_RDWR), 0664);
	if (ret < 0)
		perror("open");
	cr_assert_geq(ret, 0, "open failed! ret is %i", ret);
	ret = symlink(filename, linkname);
	if (ret < 0)
		perror("symlink");
	cr_assert_geq(ret, 0, "symlink failed! ret is %i", ret);
	char **argv = ft_strsplit(input1, ' ');
	t_shell *shell = init_shell(false);
	cr_assert_not_null(argv, "SETUP FAILED");
	cr_assert_not_null(shell, "SETUP FAILED");
	ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
	argv = ft_strsplit(input2, ' ');
	cr_assert_not_null(argv, "SECOND SETUP FAILED");
	expected_ret = 0;
	ret = builtin_test(shell, argv);
	cr_expect_eq(expected_ret, ret, "expected ret %i but got %i", expected_ret, ret);
	remove(filename);
	remove(linkname);
}
