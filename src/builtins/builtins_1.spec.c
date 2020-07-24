/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_1.spec.c                                  :+:    :+:            */
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
#include <stdio.h>

#include "builtins.h"
#include "environment.h"

static void redirect_std_out()
{
	cr_redirect_stdout();
}

static void redirect_std_err_out()
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

Test(execute_builtin_unit, invalid_argv_null)
{
	int ret = execute_builtin(NULL, NULL);
	cr_assert_eq(ret, -1);
}

Test(execute_builtin_unit, invalid_NULL_argv)
{
	char		**argv;
	int			ret = 0;

	argv = NULL;
	ret = execute_builtin(NULL, argv);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}

Test(execute_builtin_unit, invalid_NULL_argv_zero)
{
	char		**argv;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 1);
	argv[0] = NULL;
	ret = execute_builtin(NULL, argv);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}

Test(execute_builtin_unit, invalid_not_builtin)
{
	char		**argv;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 2);
	argv[0] = ft_strdup("foo");
	argv[1] = NULL;
	ret = execute_builtin(NULL, argv);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}

Test(execute_builtin_echo_unit, valid_echo_no_arguments, .init = redirect_std_err_out)
{
	char		**argv;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("echo");
	argv[1] = NULL;
	ret = execute_builtin(NULL, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "\n");
	cr_expect_stdout_eq_str(buff);
	memset(buff, '\0', 1024);
	dprintf(2, "-");
	fflush(stderr);
	cr_expect_stderr_eq_str("-");
}

Test(builtin_echo_unit, invalid_NULL_argv)
{
	char		**argv;
	int			ret = 0;

	argv = NULL;
	ret = builtin_echo(NULL, argv);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}

Test(builtin_echo_unit, valid_echo_no_arguments, .init = redirect_std_out)
{
	char		**argv;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("echo");
	argv[1] = NULL;
	ret = builtin_echo(NULL, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "\n");
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_echo_unit, valid_echo_only_no_newline, .init = redirect_std_out)
{
	char		**argv;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("-n");
	argv[2] = NULL;
	ret = builtin_echo(NULL, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	ft_printf("-");
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "-");
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_echo_unit, valid_echo_one_argument, .init = redirect_std_out)
{
	char		**argv;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("foo");
	argv[2] = NULL;
	ret = builtin_echo(NULL, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s\n", argv[1]);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_echo_unit, valid_echo_one_argument_no_newline, .init = redirect_std_out)
{
	char		**argv;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("-n");
	argv[2] = ft_strdup("foo");
	argv[3] = NULL;
	ret = builtin_echo(NULL, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s", argv[2]);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_echo_unit, valid_echo_two_arguments_no_newline, .init = redirect_std_out)
{
	char		**argv;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("-n");
	argv[2] = ft_strdup("foo");
	argv[3] = ft_strdup("bar");
	argv[4] = NULL;
	ret = builtin_echo(NULL, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s %s", argv[2], argv[3]);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_echo_unit, valid_echo_two_arguments, .init = redirect_std_out)
{
	char		**argv;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("echo");
	argv[1] = ft_strdup("foo");
	argv[2] = ft_strdup("bar");
	argv[3] = NULL;
	ret = builtin_echo(NULL, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s %s\n", argv[1], argv[2]);
	cr_expect_stdout_eq_str(buff);
}

Test(is_builtin_unit, valid_cd_builtin)
{
	cr_expect_eq(is_builtin("cd"), 1);
}

Test(is_builtin_unit, valid_echo_builtin)
{
	cr_expect_eq(is_builtin("echo"), 1);
}

Test(is_builtin_unit, valid_exit_builtin)
{
	cr_expect_eq(is_builtin("exit"), 1);
}

Test(is_builtin_unit, valid_setenv_builtin)
{
	cr_expect_eq(is_builtin("setenv"), 1);
}

Test(is_builtin_unit, valid_unsetenv_builtin)
{
	cr_expect_eq(is_builtin("unsetenv"), 1);
}

Test(is_builtin_unit, valid_setshell_builtin)
{
	cr_expect_eq(is_builtin("setshell"), 1);
}

Test(is_builtin_unit, valid_shellenv_builtin)
{
	cr_expect_eq(is_builtin("set"), 1);
}

Test(is_builtin_unit, valid_unsetshell_builtin)
{
	cr_expect_eq(is_builtin("unsetshell"), 1);
}

Test(is_builtin_unit, invalid_foo)
{
	cr_expect_eq(is_builtin("foo"), 0);
}
