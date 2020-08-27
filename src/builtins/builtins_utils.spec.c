/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_utils.spec.c                              :+:    :+:            */
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

Test(is_builtin_unit, valid_cd_builtin)
{
	cr_expect_eq(is_builtin("cd"), true);
}

Test(is_builtin_unit, valid_echo_builtin)
{
	cr_expect_eq(is_builtin("echo"), true);
}

Test(is_builtin_unit, valid_exit_builtin)
{
	cr_expect_eq(is_builtin("exit"), true);
}

Test(is_builtin_unit, valid_setenv_builtin)
{
	cr_expect_eq(is_builtin("setenv"), true);
}

Test(is_builtin_unit, valid_unsetenv_builtin)
{
	cr_expect_eq(is_builtin("unsetenv"), true);
}

Test(is_builtin_unit, valid_setshell_builtin)
{
	cr_expect_eq(is_builtin("setshell"), true);
}

Test(is_builtin_unit, valid_shellenv_builtin)
{
	cr_expect_eq(is_builtin("set"), true);
}

Test(is_builtin_unit, valid_unsetshell_builtin)
{
	cr_expect_eq(is_builtin("unsetshell"), true);
}

Test(is_builtin_unit, invalid_foo)
{
	cr_expect_eq(is_builtin("foo"), false);
}
