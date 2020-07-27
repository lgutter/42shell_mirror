/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.spec.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 09:29:48 by lgutter       #+#    #+#                 */
/*   Updated: 2020/02/07 12:10:34 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include <stdio.h>
#include "builtins.h"
#include "error_str.h"

static void redirect_std_err(void)
{
	cr_redirect_stderr();
}

Test(unit_builtin_exit, basic_mandatory_exit_status_code_42)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret;
	char		*temp;

	ft_setenv(shell->env, "?", "42", SHELL_VAR);
	argv = ft_strsplit("exit", ' ');
	ret = builtin_exit(shell, argv);
	cr_expect_eq(ret, exit_shell_code, "expected ret %i, got %i!", exit_shell_code, ret);
	temp = ft_getenv(shell->env, "EXIT_CODE", SHELL_VAR);
	cr_expect_str_eq(temp, "42", "expected exit code var %s, got %s!", "42", temp);
}

Test(unit_builtin_exit, basic_mandatory_error_no_exit_code)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret;
	char		*temp;

	ft_setenv(shell->env, "FOO", "BAR", SHELL_VAR);
	argv = ft_strsplit("exit", ' ');
	ret = builtin_exit(shell, argv);
	cr_expect_eq(ret, exit_shell_code, "expected ret %i, got %i!", exit_shell_code, ret);
	temp = ft_getenv(shell->env, "EXIT_CODE", SHELL_VAR);
	cr_expect_str_eq(temp, "0", "expected exit code var %s, got %s!", "0", temp);
}

Test(unit_builtin_exit, basic_mandatory_error_NULL_argv_1)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret;
	char		*temp;

	ft_setenv(shell->env, "FOO", "BAR", SHELL_VAR);
	argv = ft_strsplit("exit", ' ');
	ret = builtin_exit(shell, argv);
	cr_expect_eq(ret, exit_shell_code, "expected ret %i, got %i!", exit_shell_code, ret);
	temp = ft_getenv(shell->env, "EXIT_CODE", SHELL_VAR);
	cr_expect_str_eq(temp, "0", "expected exit code var %s, got %s!", "0", temp);
}

Test(unit_builtin_exit, basic_mandatory_error_NULL_argv_0)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret;
	char		*temp;

	ft_setenv(shell->env, "FOO", "BAR", SHELL_VAR);
	argv = (char **)malloc(sizeof(char *) * 1);
	argv[0] = NULL;
	ret = builtin_exit(shell, argv);
	cr_expect_eq(ret, exit_shell_code, "expected ret %i, got %i!", exit_shell_code, ret);
	temp = ft_getenv(shell->env, "EXIT_CODE", SHELL_VAR);
	cr_expect_str_eq(temp, "0", "expected exit code var %s, got %s!", "0", temp);
}

Test(unit_builtin_exit, basic_mandatory_error_NULL_shell)
{
	char		**argv;
	int			ret;

	argv = ft_strsplit("exit", ' ');
	ret = builtin_exit(NULL, argv);
	cr_expect_eq(ret, exit_shell_code, "expected ret %i, got %i!", exit_shell_code, ret);
}

Test(unit_builtin_exit, basic_mandatory_error_NULL_argv)
{
	t_shell		*shell = init_shell(false);
	int			ret;
	char		*temp;

	ret = builtin_exit(shell, NULL);
	cr_expect_eq(ret, exit_shell_code, "expected ret %i, got %i!", exit_shell_code, ret);
	temp = ft_getenv(shell->env, "EXIT_CODE", SHELL_VAR);
	cr_expect_str_eq(temp, "0", "expected exit code var %s, got %s!", "0", temp);
}

Test(unit_builtin_exit, basic_mandatory_error_running_jobs, .init = cr_redirect_stderr)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	t_job		*job = init_job(shell, "sleep 42 &", false);
	t_job_cont	job_control;
	job_control.job_list = job;
	shell->job_control = &job_control;
	char		*temp;
	int			ret;


	argv = ft_strsplit("exit", ' ');
	ret = builtin_exit(shell, argv);
	cr_expect_eq(ret, 0, "expected ret %i, got %i!", 0, ret);
	temp = ft_getenv(shell->env, "EXIT_CODE", SHELL_VAR);
	cr_expect_null(temp);
	fflush(stderr);
	cr_expect_stderr_eq_str("Cetushell: you have unfinished jobs.\n");
}

Test(unit_builtin_exit, undefined_error_nothing_defined, .init = redirect_std_err)
{
	t_shell		*shell = init_shell(false);
	char		**argv;
	int			ret;
	char		*temp;
	char		buff[1024];

	shell->env = NULL;
	argv = NULL;
	ret = builtin_exit(shell, argv);
	cr_expect_eq(ret, exit_shell_code, "expected ret %i, got %i!", exit_shell_code, ret);
	temp = ft_getenv(shell->env, "EXIT_CODE", SHELL_VAR);
	cr_expect_null(temp);
	fflush(stderr);
	sprintf(buff, "Cetushell: %.1000s\n", g_error_str[env_empty_error]);
	cr_expect_stderr_eq_str(buff);
}

Test(unit_builtin_exit, basic_bonus_error_valid_argument_exit_code)
{
	char		**argv;
	t_shell		*shell = init_shell(false);
	int			ret;
	char		*temp;

	ft_setenv(shell->env, "FOO", "BAR", SHELL_VAR);
	argv = ft_strsplit("exit 45", ' ');
	ret = builtin_exit(shell, argv);
	cr_expect_eq(ret, exit_shell_code, "expected ret %i, got %i!", exit_shell_code, ret);
	temp = ft_getenv(shell->env, "EXIT_CODE", SHELL_VAR);
	cr_expect_str_eq(temp, "45", "expected exit code var %s, got %s!", "45", temp);
}

