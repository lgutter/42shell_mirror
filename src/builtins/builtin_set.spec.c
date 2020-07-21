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
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("setenv");
	argv[1] = ft_strdup("0test=dit");
	argv[2] = NULL;
	ret = builtin_set(shell, argv);
	cr_assert_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	sprintf(buff, "Cetushell: %s: 0test: %s\n", argv[0], g_error_str[error_inv_format]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_set_env_unit, invalid_too_many_equals_signs, .init = redirect_std_err)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("setenv");
	argv[1] = ft_strdup("test=foo=bar");
	argv[2] = NULL;
	ret = builtin_set(shell, argv);
	cr_assert_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	sprintf(buff, "Cetushell: %s: test=foo=bar: %s\n", argv[0], g_error_str[error_inv_format]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_set_env_unit, invalid_spaces_in_key, .init = redirect_std_err)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("setenv");
	argv[1] = ft_strdup("te st=foo");
	argv[2] = NULL;
	ret = builtin_set(shell, argv);
	cr_assert_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	sprintf(buff, "Cetushell: %s: te st: %s\n", argv[0], g_error_str[error_inv_format]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_set_env_unit, invalid_deny_read_only_overwrite, .init = redirect_std_err)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];

	ft_setenv(shell->env, "READONLY", "ORIGINAL", (RO_VAR | ENV_VAR));
	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("setenv");
	argv[1] = ft_strdup("--readonly");
	argv[2] = ft_strdup("READONLY=OVERWRITTEN");
	argv[3] = NULL;
	ret = builtin_set(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	sprintf(buff, "Cetushell: %s: READONLY: %s\n", argv[0], g_error_str[error_ronly]);
	cr_expect_stderr_eq_str(buff);
	cr_expect_str_eq(ft_getenv(shell->env, "READONLY", ENV_VAR), "ORIGINAL");
}

Test(builtin_set_env_unit, valid_force_read_only_overwrite)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;

	ft_setenv(shell->env, "READONLY", "ORIGINAL", (RO_VAR | ENV_VAR));
	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("setenv");
	argv[1] = ft_strdup("--force");
	argv[2] = ft_strdup("READONLY=OVERWRITTEN");
	argv[3] = NULL;
	ret = builtin_set(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(shell->env, "READONLY", ENV_VAR), "OVERWRITTEN");
}

Test(builtin_set_env_unit, valid_normal_overwrite)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;

	ft_setenv(shell->env, "NORMALVAR", "ORIGINAL", ENV_VAR);
	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("setenv");
	argv[1] = ft_strdup("NORMALVAR=OVERWRITTEN");
	argv[2] = NULL;
	ret = builtin_set(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(shell->env, "NORMALVAR", ENV_VAR), "OVERWRITTEN");
}

Test(builtin_set_env_unit, valid_normal_no_value_overwrite)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;

	ft_setenv(shell->env, "NORMALVAR", "ORIGINAL", ENV_VAR);
	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("setenv");
	argv[1] = ft_strdup("NORMALVAR=");
	argv[2] = NULL;
	ret = builtin_set(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(shell->env, "NORMALVAR", ENV_VAR), "");
}

Test(builtin_set_env_unit, valid_normal_create_var)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;

	cr_assert_null(ft_getenv(shell->env, "NEWVAR", VAR_TYPE));
	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("setenv");
	argv[1] = ft_strdup("NEWVAR=FOO");
	argv[2] = NULL;
	ret = builtin_set(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(shell->env, "NEWVAR", ENV_VAR), "FOO");
}

Test(builtin_set_env_unit, valid_different_var_type)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;

	ft_setenv(shell->env, "SAMENAME", "INENVVARS", (RO_VAR | ENV_VAR));
	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("setshell");
	argv[1] = ft_strdup("--force");
	argv[2] = ft_strdup("SAMENAME=INSHELLVARS");
	argv[3] = NULL;
	ret = builtin_set(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_str_eq(ft_getenv(shell->env, "SAMENAME", SHELL_VAR), "INSHELLVARS");
	cr_expect_str_eq(ft_getenv(shell->env, "SAMENAME", ENV_VAR), "INENVVARS");
}

Test(builtin_set_env_unit, valid_print_usage, .init = redirect_std_err)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("setenv");
	argv[1] = ft_strdup("--help");
	argv[2] = NULL;
	ret = builtin_set(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	memset(buff, '\0', 1024);
	fflush(stderr);
	sprintf(buff, "Usage: %s [OPTION]... [KEY=VALUE]...\n\nOptions:\n\t--help:\tprint this usage.\n\t--readonly:\tvariables are made read only.\n\t--force:\tread only attributes are ignored.\n", argv[0]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_set_env_unit, invalid_invalid_option, .init = redirect_std_err)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret = 0;
	char		buff[1024];

	argv = (char **)malloc(sizeof(char *) * 4);
	argv[0] = ft_strdup("setenv");
	argv[1] = ft_strdup("--foo");
	argv[2] = ft_strdup("testinvalidoption=foo");
	argv[3] = NULL;
	ret = builtin_set(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	cr_expect_null(ft_getenv(shell->env, "testinvalidoption", VAR_TYPE));
	memset(buff, '\0', 1024);
	fflush(stderr);
	sprintf(buff, "Cetushell: %s: %s: %s\n", argv[0], argv[1], g_error_str[invalid_option]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_set_env_unit, valid_env_no_arguments, .init = redirect_std_out)
{
	char		**argv;
	t_env		shell_var = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell_var};
	t_env		*start = &env;
	t_shell		*shell = init_shell(false);
	shell->env = start;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("setenv");
	argv[1] = NULL;
	ret = builtin_set(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s=%s\n", env.key, env.value);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_set_env_unit, valid_shell_no_arguments, .init = redirect_std_out)
{
	char		**argv;
	t_env		shell_var = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell_var};
	t_env		*start = &env;
	t_shell		*shell = init_shell(false);
	shell->env = start;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("setshell");
	argv[1] = NULL;
	ret = builtin_set(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s=%s\n", shell_var.key, shell_var.value);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_set_env_unit, invalid_NULL_env)
{
	char		**argv;
	t_env		*start = NULL;
	t_shell		*shell = init_shell(false);
	shell->env = start;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("setshell");
	argv[1] = NULL;
	ret = builtin_set(shell, argv);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}

Test(builtin_set_env_unit, invalid_NULL_argv)
{
	char		**argv;
	t_env		shell_var = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell_var};
	t_env		*start = &env;
	t_shell		*shell = init_shell(false);
	shell->env = start;
	int			ret = 0;

	argv = NULL;
	ret = builtin_set(shell, argv);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}


Test(builtin_set_env_unit, invalid_NULL_command)
{
	t_env		shell_var = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell_var};
	t_env		*start = &env;
	t_shell		*shell = init_shell(false);
	shell->env = start;
	int			ret = 0;

	ret = builtin_set(shell, NULL);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}
