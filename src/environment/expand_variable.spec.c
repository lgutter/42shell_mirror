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
