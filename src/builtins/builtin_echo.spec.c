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

static void redirect_std_out()
{
	cr_redirect_stdout();
}

Test(builtin_echo_unit, invalid_comm_null)
{
	int ret = builtin_echo(NULL, NULL);
	cr_assert_eq(ret, -1);
}

Test(builtin_echo_unit, invalid_NULL_argv)
{
	t_command	comm;
	int			ret = 0;

	comm.argc = 1;
	comm.argv = NULL;
	ret = builtin_echo(&comm, NULL);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}

Test(builtin_echo_unit, valid_echo_no_arguments, .init = redirect_std_out)
{
	t_command	comm;
	int			ret = 0;

	comm.argc = 1;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("echo");
	comm.argv[1] = NULL;
	ret = builtin_echo(&comm, NULL);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "\n");
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_echo_unit, valid_echo_only_no_newline, .init = redirect_std_out)
{
	t_command	comm;
	int			ret = 0;

	comm.argc = 2;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("echo");
	comm.argv[1] = ft_strdup("-n");
	comm.argv[2] = NULL;
	ret = builtin_echo(&comm, NULL);
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
	t_command	comm;
	int			ret = 0;

	comm.argc = 2;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("echo");
	comm.argv[1] = ft_strdup("foo");
	comm.argv[2] = NULL;
	ret = builtin_echo(&comm, NULL);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s\n", comm.argv[1]);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_echo_unit, valid_echo_one_argument_no_newline, .init = redirect_std_out)
{
	t_command	comm;
	int			ret = 0;

	comm.argc = 3;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("echo");
	comm.argv[1] = ft_strdup("-n");
	comm.argv[2] = ft_strdup("foo");
	comm.argv[3] = NULL;
	ret = builtin_echo(&comm, NULL);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s", comm.argv[2]);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_echo_unit, valid_echo_two_arguments_no_newline, .init = redirect_std_out)
{
	t_command	comm;
	int			ret = 0;

	comm.argc = 4;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("echo");
	comm.argv[1] = ft_strdup("-n");
	comm.argv[2] = ft_strdup("foo");
	comm.argv[3] = ft_strdup("bar");
	comm.argv[4] = NULL;
	ret = builtin_echo(&comm, NULL);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s %s", comm.argv[2], comm.argv[3]);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_echo_unit, valid_echo_two_arguments, .init = redirect_std_out)
{
	t_command	comm;
	int			ret = 0;

	comm.argc = 3;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("echo");
	comm.argv[1] = ft_strdup("foo");
	comm.argv[2] = ft_strdup("bar");
	comm.argv[3] = NULL;
	ret = builtin_echo(&comm, NULL);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s %s\n", comm.argv[1], comm.argv[2]);
	cr_expect_stdout_eq_str(buff);
}
