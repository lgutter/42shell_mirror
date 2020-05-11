/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_env.spec.c                                 :+:    :+:            */
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

Test(builtin_env_unit, env_null)
{
	t_command comm;

	ft_bzero(&comm, sizeof(t_command));
	int ret = builtin_env(&comm, NULL);
	cr_assert_eq(ret, 0);
}

Test(builtin_shellenv_unit, shellenv_null)
{
	t_command comm;

	ft_bzero(&comm, sizeof(t_command));
	int ret = builtin_shellenv(&comm, NULL);
	cr_assert_eq(ret, 0);
}

Test(builtin_env_unit, valid_env_no_arguments, .init = redirect_std_out)
{
	t_command	comm;
	t_env		shell = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", (ENV_VAR | RO_VAR), &shell};
	t_env		*start = &env;
	int			ret = 0;

	comm.argc = 1;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("env");
	comm.argv[1] = NULL;
	ret = builtin_env(&comm, &start);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s=%s\n", env.key, env.value);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_shellenv_unit, valid_shell_no_arguments, .init = redirect_std_out)
{
	t_command	comm;
	t_env		shell = {"baz", "blah", (SHELL_VAR | RO_VAR), NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell};
	t_env		*start = &env;
	int			ret = 0;

	comm.argc = 1;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("shellenv");
	comm.argv[1] = NULL;
	ret = builtin_shellenv(&comm, &start);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s=%s\n", shell.key, shell.value);
	cr_expect_stdout_eq_str(buff);
}
