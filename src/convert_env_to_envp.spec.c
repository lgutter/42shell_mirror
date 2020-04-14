/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_env_to_envp.spec.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 10:30:10 by lgutter       #+#    #+#                 */
/*   Updated: 2020/01/22 14:59:50 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "environment.h"
#include <stdlib.h>

static void redirect_std_err(void)
{
	cr_redirect_stderr();
}

Test(unit_ft_convert_env_to_envp, mandatory_basic_convert_single_element, .init = redirect_std_err)
{
	char **envp;
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env) * 1);
	env->key = strdup("FOO");
	env->value = strdup("BAR");
	env->next = NULL;
	envp = convert_env_to_envp(env);
	cr_assert_neq(envp, NULL);
	cr_assert_str_eq(envp[0], "FOO=BAR");
	cr_assert_eq(envp[1], NULL);
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_convert_env_to_envp, mandatory_basic_convert_small_list, .init = redirect_std_err)
{
	char **envp;
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
	envp = convert_env_to_envp(env);
	cr_assert_neq(envp, NULL);
	cr_assert_str_eq(envp[0], "FOO=BAR");
	cr_assert_str_eq(envp[1], "BAZ=OOF");
	cr_assert_str_eq(envp[2], "RAB=ZAB");
	cr_assert_eq(envp[3], NULL);
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_convert_env_to_envp, mandatory_basic_convert_full_list, .init = redirect_std_err)
{
	char **envp;
	t_env *env;
	int i = 0;

	setenv("MINISHELL_TEST_KEY", "CONVERT_TEST_VALUE", 1);
	env = dup_sys_env();
	envp = convert_env_to_envp(env);
	cr_assert_neq(envp, NULL);
	while (envp[i] != NULL)
	{
		if (strcmp(envp[i], "MINISHELL_TEST_KEY=CONVERT_TEST_VALUE") == 0)
		{
			break;
		}
		i++;
	}
	cr_assert_str_eq(envp[i], "MINISHELL_TEST_KEY=CONVERT_TEST_VALUE");
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_convert_env_to_envp, mandatory_error_convert_NULL_list, .init = redirect_std_err)
{
	char **envp;
	t_env *env = NULL;

	envp = convert_env_to_envp(env);
	cr_assert_eq(*envp, NULL);
	dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}
