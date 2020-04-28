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
#include "environment.h"

Test(unit_ft_expand_variable, basic_mandatory_expand_tilde)
{
	t_env *env = (t_env *)malloc(sizeof(t_env) * 1);
	char *test_string = strdup("~");
	int ret;

	env->key = strdup("HOME");
	env->value = strdup("/home/criteriontest");
	env->next = NULL;
	ret = expand_variable(env, &test_string);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(test_string, "/home/criteriontest");
}

Test(unit_ft_expand_variable, basic_mandatory_expand_HOME)
{
	t_env *env = (t_env *)malloc(sizeof(t_env) * 1);
	char *test_string = strdup("$FOO");
	int ret;

	env->key = strdup("FOO");
	env->value = strdup("Barcriteriontest");
	env->next = NULL;
	ret = expand_variable(env, &test_string);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(test_string, "Barcriteriontest");
}

Test(unit_ft_expand_variable, basic_mandatory_no_key)
{
	t_env *env = (t_env *)malloc(sizeof(t_env) * 1);
	char *test_string = strdup("$.FOO");
	int ret;

	env->key = strdup("FOO");
	env->value = strdup("Barcriteriontest");
	env->next = NULL;
	ret = expand_variable(env, &test_string);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(test_string, "$.FOO");
}

Test(unit_ft_expand_variable, basic_mandatory_loop_key, .timeout = 2)
{
	t_env *env = (t_env *)malloc(sizeof(t_env) * 1);
	char *test_string = strdup("$FOO");
	int ret;

	env->key = strdup("FOO");
	env->value = strdup("$FOO");
	env->next = NULL;
	ret = expand_variable(env, &test_string);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(test_string, "$FOO");
}

Test(unit_ft_expand_variable, basic_mandatory_error_NULL_env_list)
{
	t_env *env = NULL;
	char *test_string = strdup("$FOO");
	int ret;

	ret = expand_variable(env, &test_string);
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(test_string, "");
}

Test(unit_ft_expand_variable, basic_mandatory_error_NULL_string)
{
	t_env *env = (t_env *)malloc(sizeof(t_env) * 1);
	char *test_string = NULL;
	int ret;

	env->key = strdup("FOO");
	env->value = strdup("$FOO");
	env->next = NULL;
	ret = expand_variable(env, &test_string);
	cr_expect_eq(ret, -1);
	cr_assert_eq(test_string, NULL);
}
