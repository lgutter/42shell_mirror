/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_setenv.spec.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 17:15:37 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/08 00:04:40 by devan         ########   odam.nl         */
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

Test(unit_ft_setenv, mandatory_basic_set_new_simple, .init = redirect_std_err)
{
	int ret;
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env) * 1);
	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->next = NULL;
	ret = ft_setenv(env, "TEST_KEY", "TEST_VALUE", (RO_VAR | ENV_VAR));
	cr_assert_eq(ret, 0);
	env = env->next;
	cr_assert_str_eq(env->key, "TEST_KEY");
	cr_assert_str_eq(env->value, "TEST_VALUE");
	cr_assert_eq(env->type, (RO_VAR | ENV_VAR));
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_setenv, mandatory_basic_set_new_empty_first_element, .init = redirect_std_err)
{
	int ret;
	t_env *env;
	t_env *second;

	env = (t_env *)malloc(sizeof(t_env) * 1);
	second = (t_env *)malloc(sizeof(t_env) * 1);
	env->key = strdup("");
	env->value = strdup("");
	env->next = second;
	second->key = strdup("FOO");
	second->value = strdup("BAR");
	second->next = NULL;
	ret = ft_setenv(env, "TEST_KEY", "TEST_VALUE", (RO_VAR | ENV_VAR));
	cr_assert_eq(ret, 0);
	cr_assert_str_eq(env->key, "TEST_KEY");
	cr_assert_str_eq(env->value, "TEST_VALUE");
	cr_assert_eq(env->type, (RO_VAR | ENV_VAR));
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_setenv, mandatory_basic_set_new_full_list, .init = redirect_std_err)
{
	int ret;
	t_env *env;
	t_env *current;

	env = dup_sys_env();
	current = env;
	ret = ft_setenv(env, "CETUSHELL_TEST_KEY", "TEST_VALUE", (RO_VAR | ENV_VAR));
	cr_assert_eq(ret, 0);
	while (current != NULL)
	{
		if (strcmp(current->key, "CETUSHELL_TEST_KEY") == 0)
		{
			cr_assert_str_eq(current->value, "TEST_VALUE");
			cr_assert_eq(current->type, (RO_VAR | ENV_VAR));
			break;
		}
		current = current->next;
	}
	cr_assert_neq(current, NULL);
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_setenv, mandatory_basic_overwrite_in_full_list, .init = redirect_std_err)
{
	int ret;
	t_env *env;
	t_env *current;

	setenv("CETUSHELL_TEST_KEY", "FIRST_TEST_VALUE", 1);
	env = dup_sys_env();
	current = env;
	ret = ft_setenv(env, "CETUSHELL_TEST_KEY", "TEST_VALUE_NEW",  ENV_VAR);
	cr_assert_eq(ret, 0);
	while (current != NULL)
	{
		if (strcmp(current->key, "CETUSHELL_TEST_KEY") == 0)
		{
			cr_assert_str_eq(current->value, "TEST_VALUE_NEW");
			break;
		}
		current = current->next;
	}
	cr_assert_neq(current, NULL);
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_setenv, mandatory_error_deny_overwrite_in_full_list)
{
	int ret;
	t_env *env;
	t_env *current;

	env = dup_sys_env();
	current = env;
	ft_setenv(env, "CETUSHELL_TEST_KEY", "FIRST_TEST_VALUE", (RO_VAR | ENV_VAR));
	ret = ft_setenv(env, "CETUSHELL_TEST_KEY", "TEST_VALUE_NEW", (RO_VAR | ENV_VAR));
	cr_expect_eq(ret, error_ronly, "ret == %d, should be %d\n", ret, error_ronly);
	while (current != NULL)
	{
		if (strcmp(current->key, "CETUSHELL_TEST_KEY") == 0)
		{
			cr_expect_str_eq(current->value, "FIRST_TEST_VALUE");
			cr_expect_eq(current->type, (RO_VAR | ENV_VAR), "type == %i, expected %i!", current->type, (RO_VAR | ENV_VAR));
			break;
		}
		current = current->next;
	}
	cr_assert_neq(current, NULL);
}

Test(unit_ft_setenv, mandatory_error_force_overwrite_in_full_list)
{
	int ret;
	t_env *env;
	t_env *current;

	env = dup_sys_env();
	current = env;
	ft_setenv(env, "CETUSHELL_TEST_KEY", "FIRST_TEST_VALUE", (RO_VAR | ENV_VAR));
	ret = ft_setenv(env, "CETUSHELL_TEST_KEY", "TEST_VALUE_NEW", (RO_VAR | ENV_VAR | FORCE_VAR));
	cr_expect_eq(ret, 0, "ret == %d, should be %d\n", ret, 0);
	while (current != NULL)
	{
		if (strcmp(current->key, "CETUSHELL_TEST_KEY") == 0)
		{
			cr_expect_str_eq(current->value, "TEST_VALUE_NEW");
			cr_expect_eq(current->type, (RO_VAR | ENV_VAR), "type == %i, expected %i!", current->type, (RO_VAR | ENV_VAR));
			break;
		}
		current = current->next;
	}
	cr_assert_neq(current, NULL);
}

Test(unit_ft_setenv, mandatory_error_NULL_key, .init = redirect_std_err)
{
	int ret;
	t_env *env = dup_sys_env();

	ret = ft_setenv(env, NULL, "TEST_VALUE_NEW", ENV_VAR);
	cr_assert_eq(ret, -1);
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_setenv, mandatory_error_NULL_value, .init = redirect_std_err)
{
	int ret;
	t_env *env = dup_sys_env();

	ret = ft_setenv(env, "CETUSHELL_TEST_KEY", NULL, ENV_VAR);
	cr_assert_eq(ret, -1);
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_setenv, mandatory_error_NULL_list, .init = redirect_std_err)
{
	int ret;
	t_env *env = NULL;

	ret = ft_setenv(env, "CETUSHELL_TEST_KEY", "TEST_VALUE_NEW", ENV_VAR);
	cr_assert_eq(ret, env_empty_error);
	fflush(stderr);
	cr_assert_stderr_eq_str("Environment is empty\n");
}
