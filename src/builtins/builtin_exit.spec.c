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

static void redirect_std_out(void)
{
	cr_redirect_stdout();
}

static void redirect_std_err_out(void)
{
	cr_redirect_stderr();
	cr_redirect_stdout();
}

Test(unit_builtin_exit, basic_mandatory_exit_status_code_42, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);
	char		*temp;

	env->key = strdup("STATUS");
	env->value = strdup("42");
	env->type = SHELL_VAR;
	env->next = NULL;
	command.argv = ft_strsplit("exit", ' ');
	command.argc = 1;
	command.envp = NULL;
	command.path = NULL;
	ret = builtin_exit(&command, env);
	cr_expect_eq(ret, exit_shell_code, "expected ret %i, got %i!", exit_shell_code, ret);
	temp = ft_getenv(env, "EXIT_CODE", SHELL_VAR);
	cr_expect_str_eq(temp, "42", "expected exit code var %s, got %s!", "42", temp);
	fflush(stdout);
	cr_assert_stdout_eq_str("exit\n");
}

Test(unit_builtin_exit, basic_mandatory_error_no_exit_code, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);
	char		*temp;

	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->type = SHELL_VAR;
	env->next = NULL;
	command.argv = ft_strsplit("exit", ' ');
	command.argc = 1;
	command.envp = NULL;
	command.path = NULL;
	ret = builtin_exit(&command, env);
	cr_expect_eq(ret, exit_shell_code, "expected ret %i, got %i!", exit_shell_code, ret);
	temp = ft_getenv(env, "EXIT_CODE", SHELL_VAR);
	cr_expect_str_eq(temp, "0", "expected exit code var %s, got %s!", "0", temp);
	fflush(stdout);
	cr_assert_stdout_eq_str("exit\n");
}

Test(unit_builtin_exit, undefined_error_nothing_defined, .init = redirect_std_err_out)
{
	t_command	command;
	int			ret;
	t_env		*env = NULL;
	char		*temp;
	char		buff[1024];

	command.argv = NULL;
	command.argc = 0;
	command.envp = NULL;
	command.path = NULL;
	ret = builtin_exit(&command, env);
	cr_expect_eq(ret, exit_shell_code, "expected ret %i, got %i!", exit_shell_code, ret);
	temp = ft_getenv(env, "EXIT_CODE", SHELL_VAR);
	cr_expect_null(temp);
	fflush(stdout);
	cr_assert_stdout_eq_str("exit\n");
	fflush(stderr);
	sprintf(buff, "%.1022s\n", g_error_str[env_empty_error]);
	cr_expect_stderr_eq_str(buff);
}

Test(unit_builtin_exit, basic_bonus_error_valid_argument_exit_code, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);
	char		*temp;

	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->type = SHELL_VAR;
	env->next = NULL;
	command.argv = ft_strsplit("exit 45", ' ');
	command.argc = 2;
	command.envp = NULL;
	command.path = NULL;
	ret = builtin_exit(&command, env);
	cr_expect_eq(ret, exit_shell_code, "expected ret %i, got %i!", exit_shell_code, ret);
	temp = ft_getenv(env, "EXIT_CODE", SHELL_VAR);
	cr_expect_str_eq(temp, "45", "expected exit code var %s, got %s!", "45", temp);
	fflush(stdout);
	cr_assert_stdout_eq_str("exit\n");
}

