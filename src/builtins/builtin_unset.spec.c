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
	char		**argv;
	int			ret = 0;
	t_shell		*shell = init_shell(false);

	ft_setenv(shell->env, "READONLY", "ORIGINAL", (RO_VAR | ENV_VAR));
	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("unsetenv");
	argv[1] = ft_strdup("READONLY");
	argv[2] = NULL;
	ret = builtin_unsetvar(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	fflush(stderr);
	char		buff[1024];
	memset(buff, '\0', 1024);
	sprintf(buff, "Cetushell: %s: READONLY: %s\n", argv[0], g_error_str[error_ronly]);
	cr_expect_stderr_eq_str(buff);
	cr_expect_str_eq(ft_getenv(shell->env, "READONLY", ENV_VAR), "ORIGINAL");
}

Test(builtin_unset_env_unit, valid_force_read_only_unset)
{
	char		**argv;
	int			ret = 0;
	t_shell		*shell = init_shell(false);

	ft_setenv(shell->env, "READONLY", "ORIGINAL", (RO_VAR | ENV_VAR));
	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("unsetenv");
	argv[1] = ft_strdup("--force");
	argv[2] = ft_strdup("READONLY");
	argv[3] = NULL;
	ret = builtin_unsetvar(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_null(ft_getenv(shell->env, "READONLY", ENV_VAR));
}

Test(builtin_unset_env_unit, valid_normal_unset)
{
	char		**argv;
	int			ret = 0;
	t_shell		*shell = init_shell(false);

	ft_setenv(shell->env, "NORMALVAR", "ORIGINAL", ENV_VAR);
	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("unsetenv");
	argv[1] = ft_strdup("NORMALVAR");
	argv[2] = NULL;
	ret = builtin_unsetvar(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	cr_expect_null(ft_getenv(shell->env, "NORMALVAR", ENV_VAR));
}

Test(builtin_unset_env_unit, valid_print_usage, .init = redirect_std_err)
{
	char		**argv;
	int			ret = 0;
	t_shell		*shell = init_shell(false);
	char		buff[1024];

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("unsetenv");
	argv[1] = ft_strdup("--help");
	argv[2] = NULL;
	ret = builtin_unsetvar(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	memset(buff, '\0', 1024);
	fflush(stderr);
	sprintf(buff, "Usage: %s [OPTION]... [KEY=VALUE]...\n\nOptions:\n\t--help:\tprint this usage.\n\t--force:\tread only attributes are ignored.\n", argv[0]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_unset_env_unit, invalid_invalid_option, .init = redirect_std_err)
{
	char		**argv;
	int			ret = 0;
	t_shell		*shell = init_shell(false);
	char		buff[1024];

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("unsetenv");
	argv[1] = ft_strdup("--foo");
	argv[2] = ft_strdup("testinvalidoption=foo");
	argv[3] = NULL;
	ret = builtin_unsetvar(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	cr_expect_null(ft_getenv(shell->env, "testinvalidoption", VAR_TYPE));
	memset(buff, '\0', 1024);
	fflush(stderr);
	sprintf(buff, "Cetushell: %s: %s: %s\n", argv[0], argv[1], g_error_str[invalid_option]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_unset_env_unit, invalid_shell_no_arguments, .init = redirect_std_err)
{
	char		**argv;
	t_env		shell_var = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell_var};
	t_env		*start = &env;
	int			ret = 0;
	t_shell		*shell = init_shell(false);
	shell->env = start;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("unsetshell");
	argv[1] = NULL;
	ret = builtin_unsetvar(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stderr);
	sprintf(buff, "Cetushell: %s: %s\n", argv[0], g_error_str[too_few_arguments]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_unset_env_unit, invalid_NULL_env)
{
	char		**argv;
	t_env		*start = NULL;
	int			ret = 0;
	t_shell		*shell = init_shell(false);
	shell->env = start;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("unsetshell");
	argv[1] = NULL;
	ret = builtin_unsetvar(shell, argv);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}

Test(builtin_unset_env_unit, invalid_NULL_argv)
{
	char		**argv;
	t_env		shell_var = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell_var};
	t_env		*start = &env;
	int			ret = 0;
	t_shell		*shell = init_shell(false);
	shell->env = start;

	argv = NULL;
	ret = builtin_unsetvar(shell, argv);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}

Test(builtin_unset_env_unit, invalid_NULL_command)
{
	t_env		shell_var = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell_var};
	t_env		*start = &env;
	int			ret = 0;
	t_shell		*shell = init_shell(false);
	shell->env = start;

	ret = builtin_unsetvar(shell, NULL);
	cr_expect_eq(ret, -1, "ret is %d but must be %d", ret, -1);
}
