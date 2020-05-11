/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_word.spec.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/23 17:13:52 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/23 17:13:52 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "handle_input.h"

Test(process_word_unit, valid_no_processing_needed)
{
	char 	*input = strdup("hello");
	t_env	*env_list = NULL;
	int		ret;
	char *	expected_str = "hello";
	int		expected_ret = 0;

	ret = process_word(NULL, env_list, &input, 'y');
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", input, expected_str);
}

Test(process_word_unit, valid_quote_removal)
{
	char 	*input = strdup("\"hel\\lo\"");
	t_env	*env_list = NULL;
	int		ret;
	char *	expected_str = "hello";
	int		expected_ret = 0;

	ret = process_word(NULL, env_list, &input, 'y');
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", input, expected_str);
}

Test(process_word_unit, valid_environment_expansion_quotes)
{
	char 	*input = strdup("\"$FOO\"");
	t_env	*env_list = (t_env *)malloc(sizeof(t_env) * 1);
	int		ret;
	char *	expected_str = "hel\\lo";
	int		expected_ret = 0;

	env_list->key = strdup("FOO");
	env_list->value = strdup("hel\\lo");
	env_list->type = ENV_VAR;
	env_list->next = NULL;
	ret = process_word(NULL, env_list, &input, 'y');
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", input, expected_str);
}

Test(process_word_unit, valid_environment_expansion)
{
	char 	*input = strdup("$FOO");
	t_env	*env_list = (t_env *)malloc(sizeof(t_env) * 1);
	int		ret;
	char *	expected_str = "hel\\lo";
	int		expected_ret = 0;

	env_list->key = strdup("FOO");
	env_list->value = strdup("hel\\lo");
	env_list->type = ENV_VAR;
	env_list->next = NULL;
	ret = process_word(NULL, env_list, &input, 'y');
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", input, expected_str);
}

Test(process_word_unit, valid_environment_expansion_not_allowed)
{
	char 	*input = strdup("$FOO");
	t_env	*env_list = (t_env *)malloc(sizeof(t_env) * 1);
	int		ret;
	char *	expected_str = "$FOO";
	int		expected_ret = 0;

	env_list->key = strdup("FOO");
	env_list->value = strdup("hel\\lo");
	env_list->type = ENV_VAR;
	env_list->next = NULL;
	ret = process_word(NULL, env_list, &input, 'n');
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", input, expected_str);
}

Test(process_word_unit, invalid_NULL_input)
{
	char 	*input = NULL;
	t_env	*env_list = NULL;
	int		ret;
	int		expected_ret = -1;

	ret = process_word(NULL, env_list, &input, 'y');
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_eq(input, NULL);
}

Test(process_word_unit, invalid_NULL_input_pointer)
{
	t_env	*env_list = NULL;
	int		ret;
	int		expected_ret = -1;

	ret = process_word(NULL, env_list, NULL, 'y');
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
}

Test(process_word_unit, valid_expansion_NULL_env_list)
{
	char 	*input = strdup("foo$FOO");
	int		ret;
	char *	expected_str = "foo";
	int		expected_ret = 0;

	ret = process_word(NULL, NULL, &input, 'y');
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", input, expected_str);
}

Test(process_word_unit, invalid_quote_completion_NULL_shell)
{
	char 	*input = strdup("\"hel\\lo");
	t_env	*env_list = NULL;
	int		ret;
	char *	expected_str = "\"hel\\lo";
	int		expected_ret = -1;

	ret = process_word(NULL, env_list, &input, 'y');
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", input, expected_str);
}