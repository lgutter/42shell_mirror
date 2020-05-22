/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.spec.c                               :+:    :+:            */
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

static void redirect_std_err()
{
	cr_redirect_stderr();
}

Test(builtin_unset_env_unit, invalid_deny_read_only_unset, .init = redirect_std_err)
{
	t_command	comm;
	t_env		*env = dup_sys_env();
	int			ret = 0;

	ft_setenv(env, "READONLY", "ORIGINAL", (RO_VAR | ENV_VAR));
	comm.argc = 2;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("unsetenv");
	comm.argv[1] = ft_strdup("READONLY");
	comm.argv[2] = NULL;
	ret = builtin_unset(&comm, env);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	char		buff[1024];
	memset(buff, '\0', 1024);
	sprintf(buff, "%s: READONLY: %s\n", comm.argv[0], g_error_str[error_ronly]);
	cr_expect_stderr_eq_str(buff);
	cr_expect_str_eq(ft_getenv(env, "READONLY", ENV_VAR), "ORIGINAL");
}

Test(builtin_unset_env_unit, valid_force_read_only_unset)
{
	t_command	comm;
	t_env		*env = dup_sys_env();
	int			ret = 0;

	ft_setenv(env, "READONLY", "ORIGINAL", (RO_VAR | ENV_VAR));
	comm.argc = 3;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("unsetenv");
	comm.argv[1] = ft_strdup("--force");
	comm.argv[2] = ft_strdup("READONLY");
	comm.argv[3] = NULL;
	ret = builtin_unset(&comm, env);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_null(ft_getenv(env, "READONLY", ENV_VAR));
}

Test(builtin_unset_env_unit, valid_normal_unset)
{
	t_command	comm;
	t_env		temp = {"foo", "bar", ENV_VAR, NULL};
	t_env		*env = &temp;
	int			ret = 0;

	ft_setenv(env, "NORMALVAR", "ORIGINAL", ENV_VAR);
	comm.argc = 2;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("unsetenv");
	comm.argv[1] = ft_strdup("NORMALVAR");
	comm.argv[2] = NULL;
	ret = builtin_unset(&comm, env);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_null(ft_getenv(env, "NORMALVAR", ENV_VAR));
}

Test(builtin_unset_env_unit, valid_print_usage, .init = redirect_std_err)
{
	t_command	comm;
	t_env		*env = dup_sys_env();
	int			ret = 0;
	char		buff[1024];

	comm.argc = 2;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("unsetenv");
	comm.argv[1] = ft_strdup("--help");
	comm.argv[2] = NULL;
	ret = builtin_unset(&comm, env);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	memset(buff, '\0', 1024);
	fflush(stderr);
	sprintf(buff, "Usage: %s [OPTION]... [KEY=VALUE]...\n\nOptions:\n\t--help:\tprint this usage.\n\t--force:\tread only attributes are ignored.\n", comm.argv[0]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_unset_env_unit, invalid_invalid_option, .init = redirect_std_err)
{
	t_command	comm;
	t_env		*env = dup_sys_env();
	int			ret = 0;
	char		buff[1024];

	comm.argc = 3;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("unsetenv");
	comm.argv[1] = ft_strdup("--foo");
	comm.argv[2] = ft_strdup("testinvalidoption=foo");
	comm.argv[3] = NULL;
	ret = builtin_unset(&comm, env);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	cr_expect_null(ft_getenv(env, "testinvalidoption", VAR_TYPE));
	memset(buff, '\0', 1024);
	fflush(stderr);
	sprintf(buff, "%s: %s: %s\n", comm.argv[0], comm.argv[1], g_error_str[invalid_option]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_unset_env_unit, invalid_shell_no_arguments, .init = redirect_std_err)
{
	t_command	comm;
	t_env		shell = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell};
	t_env		*start = &env;
	int			ret = 0;

	comm.argc = 1;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("unsetshell");
	comm.argv[1] = NULL;
	ret = builtin_unset(&comm, start);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stderr);
	sprintf(buff, "%s: %s\n", comm.argv[0], g_error_str[too_few_arguments]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_unset_env_unit, invalid_NULL_env)
{
	t_command	comm;
	t_env		*start = NULL;
	int			ret = 0;

	comm.argc = 1;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("unsetshell");
	comm.argv[1] = NULL;
	ret = builtin_unset(&comm, start);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}

Test(builtin_unset_env_unit, invalid_NULL_argv)
{
	t_command	comm;
	t_env		shell = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell};
	t_env		*start = &env;
	int			ret = 0;

	comm.argc = 1;
	comm.argv = NULL;
	ret = builtin_unset(&comm, start);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}

Test(builtin_unset_env_unit, invalid_NULL_command)
{
	t_env		shell = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell};
	t_env		*start = &env;
	int			ret = 0;

	ret = builtin_unset(NULL, start);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}
