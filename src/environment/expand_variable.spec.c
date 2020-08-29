/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_variable.spec.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 15:28:21 by lgutter       #+#    #+#                 */
/*   Updated: 2020/02/15 13:32:15 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include <string.h>
#include <fcntl.h>
#include "processing.h"

Test(unit_ft_expand_home, basic_mandatory_expand_tilde)
{
	t_env *env = (t_env *)malloc(sizeof(t_env) * 1);
	char *test_string = strdup("~");
	size_t	write = 0;
	size_t	read = 0;
	int ret;

	env->key = strdup("HOME");
	env->value = strdup("/home/criteriontest");
	env->type = ENV_VAR;
	env->next = NULL;
	ret = expand_home(env, &test_string, &read, &write);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(test_string, "/home/criteriontest");
}

Test(unit_ft_expand_home, basic_mandatory_expand_tilde_slash)
{
	t_env *env = (t_env *)malloc(sizeof(t_env) * 1);
	char *test_string = strdup("~/");
	size_t	write = 0;
	size_t	read = 0;
	int ret;

	env->key = strdup("HOME");
	env->value = strdup("/home/criteriontest");
	env->type = ENV_VAR;
	env->next = NULL;
	ret = expand_home(env, &test_string, &read, &write);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(test_string, "/home/criteriontest/");
}

Test(unit_ft_expand_variable, basic_mandatory_expand_longer)
{
	t_env *env = (t_env *)malloc(sizeof(t_env) * 1);
	char *test_string = strdup("$FOO");
	size_t	write = 0;
	size_t	read = 0;
	int ret;
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	shell.env = env;
	env->key = strdup("FOO");
	env->value = strdup("Barcriteriontest");
	env->type = ENV_VAR;
	env->next = NULL;
	ret = expand_variable(&shell, &test_string, &read, &write);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(test_string, "Barcriteriontest");
}

Test(unit_ft_expand_variable, basic_mandatory_expand_shorter)
{
	t_env *env = (t_env *)malloc(sizeof(t_env) * 1);
	char *test_string = strdup("$Barcriteriontest");
	size_t	write = 0;
	size_t	read = 0;
	int ret;
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	shell.env = env;
	env->key = strdup("Barcriteriontest");
	env->value = strdup("FOO");
	env->type = ENV_VAR;
	env->next = NULL;
	ret = expand_variable(&shell, &test_string, &read, &write);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(test_string, "FOO");
}

Test(unit_ft_expand_variable, basic_mandatory_no_key)
{
	t_env *env = (t_env *)malloc(sizeof(t_env) * 1);
	char *test_string = strdup("$.FOO");
	size_t	write = 0;
	size_t	read = 0;
	int ret;
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	shell.env = env;
	env->key = strdup("FOO");
	env->value = strdup("Barcriteriontest");
	env->type = ENV_VAR;
	env->next = NULL;
	ret = expand_variable(&shell, &test_string, &read, &write);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(test_string, "$.FOO");
}

Test(unit_ft_expand_variable, basic_mandatory_loop_key, .timeout = 2)
{
	t_env *env = (t_env *)malloc(sizeof(t_env) * 1);
	char *test_string = strdup("$FOO");
	size_t	write = 0;
	size_t	read = 0;
	int ret;
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	shell.env = env;
	env->key = strdup("FOO");
	env->value = strdup("$FOO");
	env->type = ENV_VAR;
	env->next = NULL;
	ret = expand_variable(&shell, &test_string, &read, &write);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(test_string, "$FOO");
}

Test(unit_ft_expand_variable, basic_mandatory_error_NULL_env_list)
{
	t_env *env = NULL;
	char *test_string = strdup("$FOO");
	size_t	write = 0;
	size_t	read = 0;
	int ret;
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	shell.env = env;
	ret = expand_variable(&shell, &test_string, &read, &write);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(test_string, "");
}

Test(unit_ft_expand_variable, basic_mandatory_error_NULL_shell)
{
	char *test_string = strdup("$FOO");
	size_t	write = 0;
	size_t	read = 0;
	int ret;
	ret = expand_variable(NULL, &test_string, &read, &write);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(test_string, "");
}

Test(unit_ft_expand_variable, basic_mandatory_error_NULL_string)
{
	t_env *env = (t_env *)malloc(sizeof(t_env) * 1);
	char *test_string = NULL;
	size_t	write = 0;
	size_t	read = 0;
	int ret;
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	shell.env = env;
	env->key = strdup("FOO");
	env->value = strdup("$FOO");
	env->type = ENV_VAR;
	env->next = NULL;
	ret = expand_variable(&shell, &test_string, &read, &write);
	cr_expect_eq(ret, -1);
	cr_assert_eq(test_string, NULL);
}

Test(unit_ft_expand_variable, mixed_command_substitution)
{

	struct {
		char *in;
		char *out;
		size_t in_read;
		size_t in_write;
		size_t out_read;
		size_t out_write;
	} test_cases[] = {
		{ .in = "$(echo hi)", .out = "hi" },
		{ .in = "$(echo $PATH)", .out = "/usr/local/bin:/usr/bin:/bin" },
		{
		  .in = "$(rm -rf /tmp/cetushell-subst-test &&"
		  "mkdir /tmp/cetushell-subst-test &&"
		  "cd /tmp/cetushell-subst-test &&"
		  "touch hello && ls &&"
		  "rm -r ../cetushell-subst-test)",

		  .out = "hello",
		},
		{ .in = "hello$(echo $PATH | head -c 5)world", .out = "hello/usr/world",
		  .in_read = 5, .in_write = 5, .out_read = 9, .out_write = 10 },
		{ .in = "helloX$(echo $PATH | head -c 5)world\"", .out = "hello/usr/world\"",
		  .in_read = 6, .in_write = 5, .out_read = 9, .out_write = 10 },
	};

	for (size_t i = 0; i < sizeof(test_cases) / sizeof(*test_cases); i++) {
		char *test_string = strdup(test_cases[i].in);

		size_t read = test_cases[i].in_read;
		size_t write = test_cases[i].in_write;

		t_shell *shell = init_shell(false);
		ft_setenv(shell->env, "PATH", "/usr/local/bin:/usr/bin:/bin", ENV_VAR);

		int ret = expand_variable(shell, &test_string, &read, &write);

		cr_expect_eq(ret, 0);
		cr_expect_str_eq(test_string, test_cases[i].out);
		if (test_cases[i].out_read != 0 && test_cases[i].out_write != 0)
		{
			cr_expect_eq(read, test_cases[i].out_read);
			cr_expect_eq(write, test_cases[i].out_write);
		}
	}
}

Test(unit_ft_expand_variable, basic_process_substitution_left) {
	char	*test_string = strdup("<(echo hi)");
	size_t	read_idx = 0, write_idx = 0;
	t_shell	*shell = init_shell(false);
	ft_setenv(shell->env, "PATH", "/usr/local/bin:/usr/bin:/bin", ENV_VAR);

	int ret = expand_variable(shell, &test_string, &read_idx, &write_idx);
	cr_expect_eq(ret, 0);
	cr_expect_eq(ft_strncmp(test_string, "/dev/fd/", 8), 0);
	int fd = open(test_string, O_RDONLY);

	char process_stdout[1024];
	size_t offset = 0;
	ssize_t n;
	while (( n = read(fd, process_stdout + offset, sizeof(process_stdout) - offset) ) > 0 ) {
			process_stdout[offset + n] = '\0';
			offset += n;
	}

	cr_assert_str_eq(process_stdout, "hi\n");
	cr_assert_eq(read(fd, process_stdout, sizeof(process_stdout)), 0);
}
