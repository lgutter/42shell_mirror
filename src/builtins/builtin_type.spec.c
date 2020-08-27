/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_type.spec.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/25 13:59:40 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/25 13:59:40 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>

#include "builtins.h"
#include "environment.h"
#include "error_str.h"

static void redirect_both()
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

Test(builtin_type_unit, invalid_NULL_argv)
{
	cr_expect_eq(builtin_type(NULL, NULL), 1);
}

Test(builtin_type_unit, invalid_NULL_argv_zero)
{
	char	*null = NULL;
	char	**argv = &null;

	cr_expect_eq(builtin_type(NULL, argv), 1);
}

Test(builtin_type_unit, valid_NULL_shell_find_builtin, .init = cr_redirect_stdout)
{
	char	**argv = ft_strsplit_t_s("type echo");
	char	*expected_output = "echo is a shell builtin\n";

	cr_expect_eq(builtin_type(NULL, argv), 0);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(builtin_type_unit, invalid_NULL_shell_find_ls, .init = cr_redirect_stderr)
{
	char	**argv = ft_strsplit_t_s("type ls");

	char	expected_error[1024];
	memset(expected_error, '\0', 1024);
	snprintf(expected_error, 1024, "Cetushell: %s: PATH\nls not found\n", g_error_str[env_not_found]);
	cr_expect_eq(builtin_type(NULL, argv), 1);
	fflush(stderr);
	cr_expect_stderr_eq_str(expected_error);
}

Test(builtin_type_unit, valid_find_builtin, .init = cr_redirect_stdout)
{
	t_shell	*shell = init_shell(false);
	char	**argv = ft_strsplit_t_s("type exit");
	char	*expected_output = "exit is a shell builtin\n";

	cr_expect_eq(builtin_type(shell, argv), 0);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(builtin_type_unit, valid_find_command, .init = cr_redirect_stdout)
{
	t_shell	*shell = init_shell(false);
	char	**argv = ft_strsplit_t_s("type more");
	char	*expected_output = "more is /usr/bin/more\n";

	cr_expect_eq(builtin_type(shell, argv), 0);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(builtin_type_unit, valid_find_both, .init = cr_redirect_stdout)
{
	t_shell	*shell = init_shell(false);
	char	**argv = ft_strsplit_t_s("type more exit");
	char	*expected_output = "more is /usr/bin/more\nexit is a shell builtin\n";

	cr_expect_eq(builtin_type(shell, argv), 0);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(builtin_type_unit, valid_find_non_existent, .init = cr_redirect_stderr)
{
	t_shell	*shell = init_shell(false);
	char	**argv = ft_strsplit_t_s("type foo");
	char	*expected_output = "foo not found\n";

	cr_expect_eq(builtin_type(shell, argv), 1);
	fflush(stderr);
	cr_expect_stderr_eq_str(expected_output);
}

Test(builtin_type_unit, valid_find_directory, .init = cr_redirect_stderr)
{
	t_shell	*shell = init_shell(false);
	char	**argv = ft_strsplit_t_s("type /tmp");
	char	*expected_output = "/tmp not found\n";

	cr_expect_eq(builtin_type(shell, argv), 1);
	fflush(stderr);
	cr_expect_stderr_eq_str(expected_output);
}

Test(builtin_type_unit, valid_find_all, .init = redirect_both)
{
	t_shell	*shell = init_shell(false);
	char	**argv = ft_strsplit_t_s("type more exit foo");
	char	*expected_output = "more is /usr/bin/more\nexit is a shell builtin\n";
	char	*expected_error = "foo not found\n";

	cr_expect_eq(builtin_type(shell, argv), 1);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
	fflush(stderr);
	cr_expect_stderr_eq_str(expected_error);
}
