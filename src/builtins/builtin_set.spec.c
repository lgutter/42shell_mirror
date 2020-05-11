/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_set.spec.c                                 :+:    :+:            */
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

static void redirect_std_out()
{
	cr_redirect_stdout();
}

Test(builtin_set_env_unit, invalid_key_bad_format, .init = redirect_std_err)
{
	t_command	comm;
	t_env		*env = dup_sys_env();
	int			ret = 0;
	char		buff[1024];

	comm.argc = 2;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("setenv");
	comm.argv[1] = ft_strdup("0test=dit");
	comm.argv[2] = NULL;
	ret = builtin_set(&comm, &env);
	cr_assert_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	sprintf(buff, "%s: 0test: %s\n", comm.argv[0], g_error_str[error_inv_format]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_set_env_unit, invalid_too_many_equals_signs, .init = redirect_std_err)
{
	t_command	comm;
	t_env		*env = dup_sys_env();
	int			ret = 0;
	char		buff[1024];

	comm.argc = 2;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("setenv");
	comm.argv[1] = ft_strdup("test=foo=bar");
	comm.argv[2] = NULL;
	ret = builtin_set(&comm, &env);
	cr_assert_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	sprintf(buff, "%s: test=foo=bar: %s\n", comm.argv[0], g_error_str[error_inv_format]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_set_env_unit, invalid_spaces_in_key, .init = redirect_std_err)
{
	t_command	comm;
	t_env		*env = dup_sys_env();
	int			ret = 0;
	char		buff[1024];

	comm.argc = 2;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("setenv");
	comm.argv[1] = ft_strdup("te st=foo");
	comm.argv[2] = NULL;
	ret = builtin_set(&comm, &env);
	cr_assert_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	sprintf(buff, "%s: te st: %s\n", comm.argv[0], g_error_str[error_inv_format]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_set_env_unit, invalid_deny_read_only_overwrite, .init = redirect_std_err)
{
	t_command	comm;
	t_env		*env = dup_sys_env();
	int			ret = 0;
	char		buff[1024];

	ft_setenv(env, "READONLY", "ORIGINAL", (RO_VAR | ENV_VAR));
	comm.argc = 3;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("setenv");
	comm.argv[1] = ft_strdup("--readonly");
	comm.argv[2] = ft_strdup("READONLY=OVERWRITTEN");
	comm.argv[3] = NULL;
	ret = builtin_set(&comm, &env);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	sprintf(buff, "%s: READONLY: %s\n", comm.argv[0], g_error_str[error_ronly]);
	cr_expect_stderr_eq_str(buff);
	cr_expect_str_eq(ft_getenv(env, "READONLY", ENV_VAR), "ORIGINAL");
}

Test(builtin_set_env_unit, valid_force_read_only_overwrite)
{
	t_command	comm;
	t_env		*env = dup_sys_env();
	int			ret = 0;

	ft_setenv(env, "READONLY", "ORIGINAL", (RO_VAR | ENV_VAR));
	comm.argc = 3;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("setenv");
	comm.argv[1] = ft_strdup("--force");
	comm.argv[2] = ft_strdup("READONLY=OVERWRITTEN");
	comm.argv[3] = NULL;
	ret = builtin_set(&comm, &env);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(env, "READONLY", ENV_VAR), "OVERWRITTEN");
}

Test(builtin_set_env_unit, valid_normal_overwrite)
{
	t_command	comm;
	t_env		*env = dup_sys_env();
	int			ret = 0;

	ft_setenv(env, "NORMALVAR", "ORIGINAL", ENV_VAR);
	comm.argc = 2;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("setenv");
	comm.argv[1] = ft_strdup("NORMALVAR=OVERWRITTEN");
	comm.argv[2] = NULL;
	ret = builtin_set(&comm, &env);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(env, "NORMALVAR", ENV_VAR), "OVERWRITTEN");
}

Test(builtin_set_env_unit, valid_normal_no_value_overwrite)
{
	t_command	comm;
	t_env		*env = dup_sys_env();
	int			ret = 0;

	ft_setenv(env, "NORMALVAR", "ORIGINAL", ENV_VAR);
	comm.argc = 2;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("setenv");
	comm.argv[1] = ft_strdup("NORMALVAR=");
	comm.argv[2] = NULL;
	ret = builtin_set(&comm, &env);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(env, "NORMALVAR", ENV_VAR), "");
}

Test(builtin_set_env_unit, valid_normal_create_var)
{
	t_command	comm;
	t_env		*env = dup_sys_env();
	int			ret = 0;

	cr_assert_null(ft_getenv(env, "NEWVAR", VAR_TYPE));
	comm.argc = 2;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("setenv");
	comm.argv[1] = ft_strdup("NEWVAR=FOO");
	comm.argv[2] = NULL;
	ret = builtin_set(&comm, &env);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(env, "NEWVAR", ENV_VAR), "FOO");
}

Test(builtin_set_env_unit, valid_different_var_type)
{
	t_command	comm;
	t_env		*env = dup_sys_env();
	int			ret = 0;

	ft_setenv(env, "SAMENAME", "INENVVARS", (RO_VAR | ENV_VAR));
	comm.argc = 3;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("setshell");
	comm.argv[1] = ft_strdup("--force");
	comm.argv[2] = ft_strdup("SAMENAME=INSHELLVARS");
	comm.argv[3] = NULL;
	ret = builtin_set(&comm, &env);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(env, "SAMENAME", SHELL_VAR), "INSHELLVARS");
	cr_expect_str_eq(ft_getenv(env, "SAMENAME", ENV_VAR), "INENVVARS");
}

Test(builtin_set_env_unit, valid_print_usage, .init = redirect_std_err)
{
	t_command	comm;
	t_env		*env = dup_sys_env();
	int			ret = 0;
	char		buff[1024];

	comm.argc = 2;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("setenv");
	comm.argv[1] = ft_strdup("--help");
	comm.argv[2] = NULL;
	ret = builtin_set(&comm, &env);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	memset(buff, '\0', 1024);
	fflush(stderr);
	sprintf(buff, "Usage: %s [OPTION]... [KEY=VALUE]...\n\nOptions:\n\t--help:\tprint this usage.\n\t--readonly:\tvariables are made read only.\n\t--force:\tread only attributes are ignored.\n", comm.argv[0]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_set_env_unit, invalid_invalid_option, .init = redirect_std_err)
{
	t_command	comm;
	t_env		*env = dup_sys_env();
	int			ret = 0;
	char		buff[1024];

	comm.argc = 3;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("setenv");
	comm.argv[1] = ft_strdup("--foo");
	comm.argv[2] = ft_strdup("testinvalidoption=foo");
	comm.argv[3] = NULL;
	ret = builtin_set(&comm, &env);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	cr_expect_null(ft_getenv(env, "testinvalidoption", VAR_TYPE));
	memset(buff, '\0', 1024);
	fflush(stderr);
	sprintf(buff, "%s: %s: %s\n", comm.argv[0], comm.argv[1], g_error_str[invalid_option]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_set_env_unit, valid_env_no_arguments, .init = redirect_std_out)
{
	t_command	comm;
	t_env		shell = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell};
	t_env		*start = &env;
	int			ret = 0;

	comm.argc = 1;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("setenv");
	comm.argv[1] = NULL;
	ret = builtin_set(&comm, &start);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s=%s\n", env.key, env.value);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_set_env_unit, valid_shell_no_arguments, .init = redirect_std_out)
{
	t_command	comm;
	t_env		shell = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell};
	t_env		*start = &env;
	int			ret = 0;

	comm.argc = 1;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("setshell");
	comm.argv[1] = NULL;
	ret = builtin_set(&comm, &start);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s=%s\n", shell.key, shell.value);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_set_env_unit, invalid_NULL_env)
{
	t_command	comm;
	t_env		*start = NULL;
	int			ret = 0;

	comm.argc = 1;
	comm.argv = (char **)malloc(sizeof(char *) * 3);
	comm.argv[0] = ft_strdup("setshell");
	comm.argv[1] = NULL;
	ret = builtin_set(&comm, &start);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}

Test(builtin_set_env_unit, invalid_NULL_argv)
{
	t_command	comm;
	t_env		shell = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell};
	t_env		*start = &env;
	int			ret = 0;

	comm.argc = 1;
	comm.argv = NULL;
	ret = builtin_set(&comm, &start);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}


Test(builtin_set_env_unit, invalid_NULL_command)
{
	t_env		shell = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell};
	t_env		*start = &env;
	int			ret = 0;

	ret = builtin_set(NULL, &start);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}
