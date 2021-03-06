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
	ret = find_executable(env, &command.path, command.argv[0], false);
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
	ret = find_executable(env, &command.path, command.argv[0], false);
	cr_expect_eq(ret, 0);
	cr_assert_not_null(command.path);
	cr_expect_str_eq(command.path, "/bin/cp");
}

Test(find_executable_unit, valid_check_builtin)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("PATH");
	env->value = strdup("foo:/bin/");
	env->type = ENV_VAR;
	env->next = NULL;

	command.argc = 2;
	command.argv = ft_strsplit("cd foo", ' ');
	command.envp = NULL;
	command.path = NULL;
	ret = find_executable(env, &command.path, command.argv[0], false);
	cr_expect_eq(ret, 0, "ret is %i, expected %i!", ret, 0);
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
	ret = find_executable(env, &command.path, command.argv[0], false);
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
	ret = find_executable(env, &command.path, command.argv[0], false);
	cr_expect_eq(ret, 0);
	cr_assert_not_null(command.path);
	cr_expect_str_eq(command.path, "/usr/bin/printf");
}

Test(find_executable_unit, invalid_error_nonexistent)
{
	t_command	command;
	int			ret;
	t_env		*env = (t_env *)malloc(sizeof(t_env) * 1);

	env->key = strdup("PATH");
	env->value = strdup("foo:/bin/:/usr/bin");
	env->type = ENV_VAR;
	env->next = NULL;

	command.argc = 2;
	command.argv = ft_strsplit("foo bar", ' ');
	command.envp = NULL;
	command.path = NULL;
	ret = find_executable(env, &command.path, command.argv[0], false);
	cr_expect_eq(ret, cmd_not_found);
	cr_expect_null(command.path);
}

Test(find_executable_unit, invalid_error_no_path_silent, .init = cr_redirect_stderr)
{
	t_command	command;
	int			ret;

	command.argc = 2;
	command.argv = ft_strsplit("foo bar", ' ');
	command.envp = NULL;
	command.path = NULL;
	ret = find_executable(NULL, &command.path, command.argv[0], false);
	cr_expect_eq(ret, env_not_found);
	cr_expect_null(command.path);

	// check if nothing was printed
	dprintf(STDERR_FILENO, "-");
	cr_expect_stderr_eq_str("-");
}

Test(find_executable_unit, invalid_error_no_path_stderr, .init = cr_redirect_stderr)
{
	t_command	command;
	int			ret;

	command.argc = 2;
	command.argv = ft_strsplit("foo bar", ' ');
	command.envp = NULL;
	command.path = NULL;
	ret = find_executable(NULL, &command.path, command.argv[0], true);
	cr_expect_eq(ret, env_not_found);
	cr_expect_null(command.path);
	cr_expect_stderr_eq_str("Cetushell: Environment key not found: PATH\n");
}
