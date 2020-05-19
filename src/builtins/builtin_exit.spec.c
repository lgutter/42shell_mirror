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

static void redirect_std_out(void)
{
	cr_redirect_stdout();
}

Test(unit_builtin_exit, basic_mandatory_exit_status_code_42, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	int			stat_loc = -1;
	pid_t	pid;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("STATUS");
	env->value = strdup("42");
	env->type = SHELL_VAR;
	env->next = NULL;
	command.argv = ft_strsplit("exit", ' ');
	command.argc = 1;
	command.envp = NULL;
	command.path = NULL;
	pid = fork();
	if (pid == 0)
	{
		builtin_exit(&command, env);
		exit(-42);
	}
	else if (pid > 0)
	{
		waitpid(pid, &stat_loc, 0);
		ret = WEXITSTATUS(stat_loc);
		cr_expect_eq(ret, 42, "expected ret %i, got %i!", 42, ret);
		fflush(stdout);
		cr_assert_stdout_eq_str("exit\n");
	}
	else
	{
		cr_assert_fail("fork failed\n");
	}
}

Test(unit_builtin_exit, basic_mandatory_error_no_exit_code, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	int			stat_loc = -1;
	pid_t	pid;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->type = SHELL_VAR;
	env->next = NULL;
	command.argv = ft_strsplit("exit", ' ');
	command.argc = 1;
	command.envp = NULL;
	command.path = NULL;
	pid = fork();
	if (pid == 0)
	{
		builtin_exit(&command, env);
		exit(-42);
	}
	else if (pid > 0)
	{
		waitpid(pid, &stat_loc, 0);
		ret = WEXITSTATUS(stat_loc);
		cr_assert_eq(ret, 0);
		fflush(stdout);
		cr_assert_stdout_eq_str("exit\n");
	}
	else
	{
		cr_assert_fail("fork failed\n");
	}
}

Test(unit_builtin_exit, undefined_error_nothing_defined, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	int			stat_loc = -1;
	pid_t	pid;
	t_env		*env = NULL;

	command.argv = NULL;
	command.argc = 0;
	command.envp = NULL;
	command.path = NULL;
	pid = fork();
	if (pid == 0)
	{
		builtin_exit(&command, env);
		exit(-42);
	}
	else if (pid > 0)
	{
		waitpid(pid, &stat_loc, 0);
		ret = WEXITSTATUS(stat_loc);
		cr_assert_eq(ret, 0);
		fflush(stdout);
		cr_assert_stdout_eq_str("exit\n");
	}
	else
	{
		cr_assert_fail("fork failed\n");
	}
}

Test(unit_builtin_exit, basic_bonus_error_valid_argument_exit_code, .init = redirect_std_out)
{
	t_command	command;
	int			ret;
	int			stat_loc = -1;
	pid_t	pid;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->type = SHELL_VAR;
	env->next = NULL;
	command.argv = ft_strsplit("exit 45", ' ');
	command.argc = 2;
	command.envp = NULL;
	command.path = NULL;
	pid = fork();
	if (pid == 0)
	{
		builtin_exit(&command, env);
		exit(-42);
	}
	else if (pid > 0)
	{
		waitpid(pid, &stat_loc, 0);
		ret = WEXITSTATUS(stat_loc);
		cr_assert_eq(ret, 45);
		fflush(stdout);
		cr_assert_stdout_eq_str("exit\n");
	}
	else
	{
		cr_assert_fail("fork failed\n");
	}
}

