/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_getenv.spec.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 17:00:36 by lgutter       #+#    #+#                 */
/*   Updated: 2020/02/04 22:20:10 by lgutter       ########   odam.nl         */
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

Test(unit_ft_getenv, mandatory_basic_get_valid_value_in_single_element_list)
{
	char *value;
	t_env *list;

	list = (t_env *)malloc(sizeof(t_env) * 1);
	list->key = strdup("MINISHELL_TEST_GET_ENV");
	list->value = strdup("VALUE_FOR_TEST_1");
	list->type = ENV_VAR;
	value = ft_getenv(list, "MINISHELL_TEST_GET_ENV", ENV_VAR);
	cr_assert_str_eq(value, "VALUE_FOR_TEST_1");
}

Test(unit_ft_getenv, mandatory_basic_get_from_NULL_list, .init = redirect_std_err)
{
	char *value;
	t_env *list = NULL;

	value = ft_getenv(list, "MINISHELL_TEST_GET_ENV", ENV_VAR);
	cr_assert_eq(NULL, value);
	ft_dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_getenv, mandatory_basic_get_valid_value_from_system_list, .init = redirect_std_err)
{
	char *value;
	t_env *list;

	setenv("MINISHELL_TEST_GET_ENV", "VALUE_FOR_TEST_3", 1);
	list = dup_sys_env();
	value = ft_getenv(list, "MINISHELL_TEST_GET_ENV", ENV_VAR);
	cr_assert_str_eq(value, "VALUE_FOR_TEST_3");
	ft_dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_getenv, mandatory_basic_get_valid_value_in_single_element_list_escape_quotes)
{
	char *value;
	t_env *list;

	list = (t_env *)malloc(sizeof(t_env) * 1);
	list->key = strdup("MINISHELL_TEST_GET_ENV");
	list->value = strdup("VALUE_\\FOR\"_TE\'ST_1");
	list->type = ENV_VAR;
	list->next = NULL;
	value = ft_getenv(list, "MINISHELL_TEST_GET_ENV", ENV_VAR | QUOTE_VAR);
	cr_assert_str_eq(value, "VALUE_\\\\FOR\\\"_TE\\\'ST_1");
}

Test(unit_ft_getenv, mandatory_basic_get_from_empty_list_escape_quotes, .init = redirect_std_err)
{
	char *value;
	t_env *list = NULL;

	value = ft_getenv(list, "MINISHELL_TEST_GET_ENV", ENV_VAR | QUOTE_VAR);
	cr_assert_eq(NULL, value);
	ft_dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_getenv, mandatory_basic_get_valid_value_from_system_list_escape_quotes, .init = redirect_std_err)
{
	char *value;
	t_env *list;

	setenv("MINISHELL_TEST_GET_ENV", "VA\'LU\"E_FOR_TES\\T_3", 1);
	list = dup_sys_env();
	value = ft_getenv(list, "MINISHELL_TEST_GET_ENV", ENV_VAR | QUOTE_VAR);
	cr_assert_str_eq(value, "VA\\\'LU\\\"E_FOR_TES\\\\T_3");
	ft_dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}

Test(unit_ft_getenv, mandatory_basic_error_NULL_string, .init = redirect_std_err)
{
	char *value;
	t_env *list = NULL;

	list = dup_sys_env();
	value = ft_getenv(list, NULL, ENV_VAR);
	cr_assert_eq(NULL, value);
	ft_dprintf(2, "-");
	fflush(stderr);
	cr_assert_stderr_eq_str("-");
}
