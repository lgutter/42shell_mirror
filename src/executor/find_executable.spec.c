/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_executable_tests.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/30 12:43:24 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/30 15:20:39 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "executor.h"
#include "error_str.h"

static void redirect_std_err()
{
	cr_redirect_stderr();
}
Test(find_executable_unit, valid_find_printf)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("PATH");
	env->value = strdup("foo:/tmp/:/usr/bin");
	env->type = ENV_VAR;
	env->next = NULL;

	command.argc = 2;
	command.argv = ft_strsplit("printf foo", ' ');
	command.envp = NULL;
	command.path = NULL;
	ret = find_executable(env, &command, command.argv[0]);
	cr_expect_eq(ret, 0);
	cr_assert_not_null(command.path);
	cr_expect_str_eq(command.path, "/usr/bin/printf");
}

Test(find_executable_unit, valid_find_cp)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("PATH");
	env->value = strdup("foo:/bin/:/usr/bin");
	env->type = ENV_VAR;
	env->next = NULL;

	command.argc = 2;
	command.argv = ft_strsplit("cp foo", ' ');
	command.envp = NULL;
	command.path = NULL;
	ret = find_executable(env, &command, command.argv[0]);
	cr_expect_eq(ret, 0);
	cr_assert_not_null(command.path);
	cr_expect_str_eq(command.path, "/bin/cp");
}

Test(find_executable_unit, valid_find_builtin)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("PATH");
	env->value = strdup("foo:/bin/:/usr/bin");
	env->type = ENV_VAR;
	env->next = NULL;

	command.argc = 2;
	command.argv = ft_strsplit("echo foo", ' ');
	command.envp = NULL;
	command.path = NULL;
	ret = find_executable(env, &command, command.argv[0]);
	cr_expect_eq(ret, 0);
	cr_assert_not_null(command.path);
	cr_expect_str_eq(command.path, "");
}

Test(find_executable_unit, valid_already_relative_path)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("PATH");
	env->value = strdup("foo:/bin/:/usr/bin");
	env->type = ENV_VAR;
	env->next = NULL;

	command.argc = 2;
	command.argv = ft_strsplit("./cetushell foo", ' ');
	command.envp = NULL;
	command.path = NULL;
	ret = find_executable(env, &command, command.argv[0]);
	cr_expect_eq(ret, 0);
	cr_assert_not_null(command.path);
	cr_expect_str_eq(command.path, "./cetushell");
}

Test(find_executable_unit, valid_already_absolute_path)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("PATH");
	env->value = strdup("foo:/bin/:/usr/bin");
	env->type = ENV_VAR;
	env->next = NULL;

	command.argc = 2;
	command.argv = ft_strsplit("/usr/bin/printf foo", ' ');
	command.envp = NULL;
	command.path = NULL;
	ret = find_executable(env, &command, command.argv[0]);
	cr_expect_eq(ret, 0);
	cr_assert_not_null(command.path);
	cr_expect_str_eq(command.path, "/usr/bin/printf");
}

Test(find_executable_unit, invalid_error_nonexistent, .init = redirect_std_err)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);
	char		buff[1024];

	env->key = strdup("PATH");
	env->value = strdup("foo:/bin/:/usr/bin");
	env->type = ENV_VAR;
	env->next = NULL;

	command.argc = 2;
	command.argv = ft_strsplit("foo bar", ' ');
	command.envp = NULL;
	command.path = NULL;
	ret = find_executable(env, &command, command.argv[0]);
	cr_expect_eq(ret, cmd_not_found);
	cr_expect_null(command.path);
	fflush(stderr);
	sprintf(buff, "%s: %s\n", g_error_str[parsing_error], command.argv[0]);
}
