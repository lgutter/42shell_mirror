/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsetenv.spec.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 20:25:34 by lgutter       #+#    #+#                 */
/*   Updated: 2020/02/07 13:16:03 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "environment.h"

static void redirect_std_err(void)
{
	cr_redirect_stderr();
}

Test(unit_ft_unsetenv, mandatory_basic_unset_first_and_only_element, .init = redirect_std_err)
{
	int ret;
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env) * 1);
	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->next = NULL;
	ret = ft_unsetenv(env, "FOO");
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(env->key, "");
	cr_assert_str_eq(env->value, "");
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_unsetenv, mandatory_basic_unset_first_element_in_list, .init = redirect_std_err)
{
	int ret;
	t_env *env;
	t_env *second;
	t_env *third;

	env = (t_env *)malloc(sizeof(t_env) * 1);
	second = (t_env *)malloc(sizeof(t_env) * 1);
	third = (t_env *)malloc(sizeof(t_env) * 1);
	env->key = strdup("FOO");
	env->value = strdup("BAR");
	second->key = strdup("BAZ");
	second->value = strdup("OOF");
	third->key = strdup("RAB");
	third->value = strdup("ZAB");
	env->next = second;
	second->next = third;
	ret = ft_unsetenv(env, "FOO");
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(env->key, "BAZ");
	cr_assert_str_eq(env->value, "OOF");
	cr_assert_eq(env->next, third);
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_unsetenv, mandatory_basic_unset_last_element_in_list, .init = redirect_std_err)
{
	int ret;
	t_env *env;
	t_env *second;
	t_env *third;

	env = (t_env *)malloc(sizeof(t_env) * 1);
	second = (t_env *)malloc(sizeof(t_env) * 1);
	third = (t_env *)malloc(sizeof(t_env) * 1);
	env->key = strdup("FOO");
	env->value = strdup("BAR");
	second->key = strdup("BAZ");
	second->value = strdup("OOF");
	third->key = strdup("RAB");
	third->value = strdup("ZAB");
	env->next = second;
	second->next = third;
	third->next = NULL;
	ret = ft_unsetenv(env, "RAB");
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(second->key, "BAZ");
	cr_assert_str_eq(second->value, "OOF");
	cr_assert_eq(second->next, NULL);
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_unsetenv, mandatory_error_unset_non_existent_element, .init = redirect_std_err)
{
	int ret;
	t_env *env;
	t_env *second;
	t_env *third;

	env = (t_env *)malloc(sizeof(t_env) * 1);
	second = (t_env *)malloc(sizeof(t_env) * 1);
	third = (t_env *)malloc(sizeof(t_env) * 1);
	env->key = strdup("FOO");
	env->value = strdup("BAR");
	second->key = strdup("BAZ");
	second->value = strdup("OOF");
	third->key = strdup("RAB");
	third->value = strdup("ZAB");
	env->next = second;
	second->next = third;
	third->next = NULL;
	ret = ft_unsetenv(env, "BAR");
	cr_assert_eq(ret, env_not_found);
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_unsetenv, mandatory_error_unset_NULL_list, .init = redirect_std_err)
{
	int ret;
	t_env *env = NULL;

	ret = ft_unsetenv(env, "FOO");
	cr_assert_eq(ret, env_empty_error);
	fflush(stderr);
	cr_assert_stderr_eq_str("Environment is empty\n");
}

Test(unit_ft_unsetenv, mandatory_error_unset_NULL_key, .init = redirect_std_err)
{
	int ret;
	t_env *env = dup_sys_env();

	ret = ft_unsetenv(env, NULL);
	cr_assert_eq(ret, -1);
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}
