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

static void redirect_std_out()
{
	cr_redirect_stdout();
}

static void redirect_std_err()
{
	cr_redirect_stderr();
}

Test(builtin_env_unit, env_null)
{
	t_shell *shell =init_shell(false);
	shell->env = NULL;
	char **argv =ft_strsplit("env", ' ');

	int ret = builtin_env(shell, argv);
	cr_assert_eq(ret, 0, "expected ret to be %i, but is %i\n", 0, ret);
}

Test(builtin_shellenv_unit, shell_null)
{
	char **argv =ft_strsplit("env", ' ');

	int ret = builtin_set(NULL, argv);
	cr_assert_eq(ret, 1);
}

Test(builtin_env_unit, valid_env_no_arguments, .init = redirect_std_out)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	t_env		shell_var = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", (ENV_VAR | RO_VAR), &shell_var};
	t_env		*start = &env;
	int			ret = 0;
	shell->env = start;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("env");
	argv[1] = NULL;
	ret = builtin_env(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s=%s\n", env.key, env.value);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_set_unit, error_set_no_args_closed_stdout, .init = redirect_std_err)
{
	char		**argv;
	t_env		shell_var = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell_var};
	t_env		*start = &env;
	t_shell		*shell = init_shell(false);
	shell->env = start;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 2);
	argv[0] = ft_strdup("set");
	argv[1] = NULL;
	close(STDOUT_FILENO);
	ret = builtin_set(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stderr);
	snprintf(buff, 1023, "Cetushell: set: write error: %s\n", g_error_str[bad_fd_error]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_env_unit, error_env_no_args_closed_stdout, .init = redirect_std_err)
{
	char		**argv;
	t_env		shell_var = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell_var};
	t_env		*start = &env;
	t_shell		*shell = init_shell(false);
	shell->env = start;
	int			ret = 0;

	argv = (char **)malloc(sizeof(char *) * 2);
	argv[0] = ft_strdup("env");
	argv[1] = NULL;
	close(STDOUT_FILENO);
	ret = builtin_set(shell, argv);
	cr_expect_eq(ret, 1, "ret is %d but must be %d", ret, 1);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stderr);
	snprintf(buff, 1023, "Cetushell: env: write error: %s\n", g_error_str[bad_fd_error]);
	cr_expect_stderr_eq_str(buff);
}

Test(builtin_shellenv_unit, valid_shell_no_arguments, .init = redirect_std_out)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	t_env		shell_var = {"baz", "blah", (SHELL_VAR | RO_VAR), NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell_var};
	t_env		*start = &env;
	int			ret = 0;
	shell->env = start;

	argv = (char **)malloc(sizeof(char *) * 3);
	argv[0] = ft_strdup("shell_varenv");
	argv[1] = NULL;
	ret = builtin_set(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s=%s\n", shell_var.key, shell_var.value);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_env_unit, valid_env_no_arguments_NULL_command, .init = redirect_std_out)
{
	t_shell		*shell = init_shell(false);
	t_env		shell_var = {"baz", "blah", SHELL_VAR, NULL};
	t_env		env = {"foo", "bar", (ENV_VAR | RO_VAR), &shell_var};
	t_env		*start = &env;
	int			ret = 0;
	shell->env = start;

	ret = builtin_env(shell, NULL);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s=%s\n", env.key, env.value);
	cr_expect_stdout_eq_str(buff);
}

Test(builtin_shellenv_unit, valid_shell_no_arguments_NULL_command, .init = redirect_std_out)
{
	t_shell		*shell = init_shell(false);
	char		*argv[2] = {"setshell", NULL};
	t_env		shell_var = {"baz", "blah", (SHELL_VAR | RO_VAR), NULL};
	t_env		env = {"foo", "bar", ENV_VAR, &shell_var};
	t_env		*start = &env;
	int			ret = 0;
	shell->env = start;

	ret = builtin_setvar(shell, argv);
	cr_expect_eq(ret, 0, "ret is %d but must be %d", ret, 0);
	char		buff[1024];
	memset(buff, '\0', 1024);
	fflush(stdout);
	sprintf(buff, "%s=%s\n", shell_var.key, shell_var.value);
	cr_expect_stdout_eq_str(buff);
}
