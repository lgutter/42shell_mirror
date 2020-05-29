/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dup_sys_env.spec.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/11 14:19:16 by lgutter       #+#    #+#                 */
/*   Updated: 2020/01/13 15:44:58 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>
#include "environment.h"
#include "history.h"

Test(unit_ft_dup_sys_env, mandatory_basic_convert_sys_environ)
{
	t_env	*start_env;
	t_env	*current;

	setenv("MINISHELLENVTEST", "TESTVALUEOFENVVAR", 1);
	setenv("MINISHELLENVTESTEMPTY", "", 1);
	start_env = dup_sys_env();
	current = start_env;
	cr_assert_neq(NULL, current);
	while (current != NULL)
	{
		cr_assert_str_not_empty(current->key);
		cr_assert_neq(current->value, NULL);
		if (strcmp(current->key, "MINISHELLENVTEST") == 0)
			cr_assert_str_eq(current->value, "TESTVALUEOFENVVAR");
		current = current->next;
	}
}

Test(unit_ft_dup_sys_env, mandatory_basic_init_empty_environ)
{
	t_env	*start_env;
	t_env	*current;
	extern char **environ;

	*environ = NULL;
	start_env = dup_sys_env();
	current = start_env;
	cr_assert_neq(NULL, current);
	cr_assert_not_null(current->key);
	cr_assert_not_null(current->value);
	cr_expect_str_eq(current->key, "PWD");
	cr_expect_str_eq(current->value, getcwd(NULL, 0));
	cr_expect_eq(current->type, ENV_VAR);
	cr_assert_not_null(current->next);
	current = current->next;
	cr_assert_not_null(current->key);
	cr_assert_not_null(current->value);
	cr_expect_str_eq(current->key, "SHLVL");
	cr_expect_str_eq(current->value, "1");
	cr_expect_eq(current->type, ENV_VAR);
	cr_assert_not_null(current->next);
	current = current->next;
	cr_assert_not_null(current->key);
	cr_assert_not_null(current->value);
	cr_expect_str_eq(current->key, "PATH");
	cr_expect_str_eq(current->value, "/bin:/usr/bin:/usr/local/bin:");
	cr_expect_eq(current->type, ENV_VAR);
	cr_assert_not_null(current->next);
	current = current->next;
	cr_assert_not_null(current->key);
	cr_assert_not_null(current->value);
	cr_expect_str_eq(current->key, "HISTSIZE");
	cr_expect_str_eq(current->value, ft_itoa(HISTSIZE));
	cr_expect_eq(current->type, SHELL_VAR | RO_VAR);
	cr_assert_not_null(current->next);
	current = current->next;
	cr_assert_not_null(current->key);
	cr_assert_not_null(current->value);
	cr_expect_str_eq(current->key, "TERM");
	cr_expect_str_eq(current->value, "vt100");
	cr_expect_eq(current->type, ENV_VAR);
	cr_expect_null(current->next);
}

Test(unit_ft_dup_sys_env, mandatory_basic_init_empty_environ_but_with_histsize)
{
	t_env	*start_env;
	t_env	*current;
	extern char **environ;

	environ[1] = NULL;
	environ[0] = "HISTSIZE=-420";
	start_env = dup_sys_env();
	current = start_env;
	cr_assert_neq(NULL, current);
	cr_assert_not_null(current->key);
	cr_assert_not_null(current->value);
	cr_expect_str_eq(current->key, "HISTSIZE");
	cr_expect_str_eq(current->value, "-420");
	cr_expect_eq(current->type, ENV_VAR);
	cr_assert_not_null(current->next);
	current = current->next;
	cr_assert_not_null(current->key);
	cr_assert_not_null(current->value);
	cr_expect_str_eq(current->key, "SHLVL");
	cr_expect_str_eq(current->value, "1");
	cr_expect_eq(current->type, ENV_VAR);
	cr_assert_not_null(current->next);
	current = current->next;
	cr_assert_not_null(current->key);
	cr_assert_not_null(current->value);
	cr_expect_str_eq(current->key, "PATH");
	cr_expect_str_eq(current->value, "/bin:/usr/bin:/usr/local/bin:");
	cr_expect_eq(current->type, ENV_VAR);
	cr_assert_not_null(current->next);
	current = current->next;
	cr_assert_neq(NULL, current);
	cr_assert_not_null(current->key);
	cr_assert_not_null(current->value);
	cr_expect_str_eq(current->key, "PWD");
	cr_expect_str_eq(current->value, getcwd(NULL, 0));
	cr_expect_eq(current->type, ENV_VAR);
	cr_assert_not_null(current->next);
	current = current->next;
	cr_assert_not_null(current->key);
	cr_assert_not_null(current->value);
	cr_expect_str_eq(current->key, "HISTSIZE");
	cr_expect_str_eq(current->value, "1");
	cr_expect_eq(current->type, SHELL_VAR | RO_VAR);
	cr_assert_not_null(current->next);
	current = current->next;
	cr_assert_not_null(current->key);
	cr_assert_not_null(current->value);
	cr_expect_str_eq(current->key, "TERM");
	cr_expect_str_eq(current->value, "vt100");
	cr_expect_eq(current->type, ENV_VAR);
	cr_expect_null(current->next);
}

Test(unit_ft_dup_sys_env, mandatory_basic_free_every_element)
{
	t_env	*start_env;
	t_env	*current;
	t_env	*old;


	start_env = dup_sys_env();
	current = start_env;
	cr_assert_neq(NULL, current);
	while (current != NULL)
	{
		free(current->key);
		free(current->value);
		old = current;
		current = current->next;
		free(old);
	}
}
