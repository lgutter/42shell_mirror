/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo.spec.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/07 22:37:17 by devan         #+#    #+#                 */
/*   Updated: 2020/05/08 01:27:21 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>

#include "builtins.h"
#include "environment.h"
#include "error_str.h"

static void redirect_std_out()
{
	cr_redirect_stdout();
}

static void redirect_std_err()
{
	cr_redirect_stderr();
}

Test(builtin_echo_unit, invalid_comm_null)
{
	int ret = builtin_echo(NULL, NULL);
	cr_assert_eq(ret, -1);
}

Test(builtin_echo_unit, invalid_NULL_argv)
{
	t_shell		*shell = init_shell(false);
	char		**argv;
	int			ret = 0;

	argv = NULL;
	ret = builtin_echo(shell, argv);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}

Test(builtin_echo_unit, valid_echo_no_arguments, .init = redirect_std_out)
{
	t_shell		*shell = init_shell(false);
	char		**argv;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("echo");
	argv[1] = NULL;
	ret = builtin_echo(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "\n");
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_echo_unit, valid_echo_only_no_newline, .init = redirect_std_out)
{
	t_shell		*shell = init_shell(false);
	char		**argv;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("-n");
	argv[2] = NULL;
	ret = builtin_echo(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	ft_printf("-");
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "-");
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_echo_unit, valid_echo_only_no_newline_closed_stdout, .init = redirect_std_err)
{
	t_shell		*shell = init_shell(false);
	char		**argv;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("-n");
	argv[2] = NULL;
	close(STDOUT_FILENO);
	ret = builtin_echo(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	dprintf(STDERR_FILENO, "-");
	memset(buff, '\0', 1024);
	fflush(stderr);
	sprintf(buff, "-");
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_echo_unit, invalid_echo_closed_stdout, .init = redirect_std_err)
{
	t_shell		*shell = init_shell(false);
	char		**argv;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 2);
	argv[0] = ft_strdup("echo");
	argv[1] = NULL;
	close(STDOUT_FILENO);
	ret = builtin_echo(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stderr);
	snprintf(buff, 1023, "Cetushell: echo: write error: %s\n", g_error_str[bad_fd_error]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_echo_unit, valid_echo_one_argument, .init = redirect_std_out)
{
	t_shell		*shell = init_shell(false);
	char		**argv;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("foo");
	argv[2] = NULL;
	ret = builtin_echo(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s\n", argv[1]);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_echo_unit, valid_echo_one_argument_no_newline, .init = redirect_std_out)
{
	t_shell		*shell = init_shell(false);
	char		**argv;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("-n");
	argv[2] = ft_strdup("foo");
	argv[3] = NULL;
	ret = builtin_echo(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s", argv[2]);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_echo_unit, valid_echo_two_arguments_no_newline, .init = redirect_std_out)
{
	t_shell		*shell = init_shell(false);
	char		**argv;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("-n");
	argv[2] = ft_strdup("foo");
	argv[3] = ft_strdup("bar");
	argv[4] = NULL;
	ret = builtin_echo(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s %s", argv[2], argv[3]);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_echo_unit, valid_echo_two_arguments, .init = redirect_std_out)
{
	t_shell		*shell = init_shell(false);
	char		**argv;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("foo");
	argv[2] = ft_strdup("bar");
	argv[3] = NULL;
	ret = builtin_echo(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s %s\n", argv[1], argv[2]);
	cr_expect_stdout_eq_str(buff);
}
