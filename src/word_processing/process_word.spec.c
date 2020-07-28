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
#include "processing.h"

Test(process_word_unit, valid_no_processing_needed)
{
	char 	*input = strdup("hello");
	int		ret;
	char *	expected_str = "hello";
	int		expected_ret = 0;

	ret = process_word(NULL, &input, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", expected_str, input);
}

Test(process_word_unit, valid_quote_removal)
{
	char 	*input = strdup("\"hel\\lo\"");
	int		ret;
	char *	expected_str = "hel\\lo";
	int		expected_ret = 0;

	ret = process_word(NULL, &input, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", expected_str, input);
}

Test(process_word_unit, valid_quote_removal_here_end)
{
	char 	*input = strdup("\"hel\\lo\"");
	int		ret;
	char *	expected_str = "hel\\lo";
	int		expected_ret = 0;

	ret = process_word(NULL, &input, HERE_END_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", expected_str, input);
}

Test(process_word_unit, valid_quote_removal_not_allowed)
{
	char 	*input = strdup("\"hel\\lo\"");
	int		ret;
	char *	expected_str = "\"hel\\lo\"";
	int		expected_ret = 0;

	ret = process_word(NULL, &input, HEREDOCS_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", expected_str, input);
}

Test(process_word_unit, valid_environment_expansion_containing_backslash_outside_of_dqoutes)
{
	char 	*input = strdup("$FOO");
	t_env	*env_list = (t_env *)malloc(sizeof(t_env) * 1);
	int		ret;
	char *	expected_str = "hel\\lo";
	int		expected_ret = 0;
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	shell.env = env_list;
	env_list->key = strdup("FOO");
	env_list->value = strdup("hel\\lo");
	env_list->type = ENV_VAR;
	env_list->next = NULL;
	ret = process_word(&shell, &input, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", expected_str, input);
}

Test(process_word_unit, valid_environment_expansion_quotes)
{
	char 	*input = strdup("\"$FOO\"");
	t_env	*env_list = (t_env *)malloc(sizeof(t_env) * 1);
	int		ret;
	char *	expected_str = "hel\\lo";
	int		expected_ret = 0;
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	shell.env = env_list;
	env_list->key = strdup("FOO");
	env_list->value = strdup("hel\\lo");
	env_list->type = ENV_VAR;
	env_list->next = NULL;
	ret = process_word(&shell, &input, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", expected_str, input);
}

Test(process_word_unit, valid_deny_expansion_single_quotes)
{
	char 	*input = strdup("\'$FOO\'");
	t_env	*env_list = (t_env *)malloc(sizeof(t_env) * 1);
	int		ret;
	char *	expected_str = "$FOO";
	int		expected_ret = 0;
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	shell.env = env_list;
	env_list->key = strdup("FOO");
	env_list->value = strdup("hel\\lo");
	env_list->type = ENV_VAR;
	env_list->next = NULL;
	ret = process_word(&shell, &input, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", expected_str, input);
}

Test(process_word_unit, valid_deny_expansion_here_end)
{
	char 	*input = strdup("$FOO");
	t_env	*env_list = (t_env *)malloc(sizeof(t_env) * 1);
	int		ret;
	char *	expected_str = "$FOO";
	int		expected_ret = 0;
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	shell.env = env_list;
	env_list->key = strdup("FOO");
	env_list->value = strdup("hel\\lo");
	env_list->type = ENV_VAR;
	env_list->next = NULL;
	ret = process_word(&shell, &input, HERE_END_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", expected_str, input);
}

Test(process_word_unit, valid_deny_quote_removal_heredoc_double_quotes)
{
	char 	*input = strdup("\"$FOO\"");
	t_env	*env_list = (t_env *)malloc(sizeof(t_env) * 1);
	int		ret;
	char *	expected_str = "\"hel\\lo\"";
	int		expected_ret = 0;
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	shell.env = env_list;
	env_list->key = strdup("FOO");
	env_list->value = strdup("hel\\lo");
	env_list->type = ENV_VAR;
	env_list->next = NULL;
	ret = process_word(&shell, &input, HEREDOCS_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", expected_str, input);
}

Test(process_word_unit, valid_heredoc_expansion_single_quotes)
{
	char 	*input = strdup("'$FOO'");
	t_env	*env_list = (t_env *)malloc(sizeof(t_env) * 1);
	int		ret;
	char *	expected_str = "'hel\\lo'";
	int		expected_ret = 0;
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	shell.env = env_list;
	env_list->key = strdup("FOO");
	env_list->value = strdup("hel\\lo");
	env_list->type = ENV_VAR;
	env_list->next = NULL;
	ret = process_word(&shell, &input, HEREDOCS_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", expected_str, input);
}

Test(process_word_unit, valid_environment_expansion)
{
	char 	*input = strdup("$FOO");
	t_env	*env_list = (t_env *)malloc(sizeof(t_env) * 1);
	int		ret;
	char *	expected_str = "hel\\lo";
	int		expected_ret = 0;
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	env_list->key = strdup("FOO");
	env_list->value = strdup("hel\\lo");
	env_list->type = ENV_VAR;
	env_list->next = NULL;
	shell.env = env_list;
	ret = process_word(&shell, &input, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", expected_str, input);
}

Test(process_word_unit, valid_multiple_environment_expansion_quotes)
{
	char 	*input = strdup("~/'$FOO hoi' '$FOO \\$HOME $HOME \\g' \"$FOO$FOO hoi' '$FOO \\$HOME $HOME \\g\"$HOME\\g");
	t_env	*env_list = (t_env *)malloc(sizeof(t_env) * 1);
	t_env	*env_list2 = (t_env *)malloc(sizeof(t_env) * 1);
	int		ret;
	char *	expected_str = "/home/lgutter\\/$FOO hoi $FOO \\$HOME $HOME \\g BAR\\BAR\\ hoi' 'BAR\\ $HOME /home/lgutter\\ \\g/home/lgutter\\g";
	int		expected_ret = 0;
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	env_list->key = strdup("FOO");
	env_list->value = strdup("BAR\\");
	env_list->type = ENV_VAR;
	env_list->next = env_list2;
	env_list2->key = strdup("HOME");
	env_list2->value = strdup("/home/lgutter\\");
	env_list2->type = ENV_VAR;
	env_list2->next = NULL;
	shell.env = env_list;
	ret = process_word(&shell, &input, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", expected_ret, ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", expected_str, input);
}

Test(process_word_unit, valid_multiple_environment_expansion_quotes_heredoc)
{
	char 	*input = strdup("~/'$FOO hoi' '$FOO \\$HOME $HOME \\g' \"$FOO$FOO hoi' '$FOO \\$HOME $HOME \\g\"$HOME\\g");
	t_env	*env_list = (t_env *)malloc(sizeof(t_env) * 1);
	t_env	*env_list2 = (t_env *)malloc(sizeof(t_env) * 1);
	int		ret;
	char *	expected_str = "~/'BAR\\ hoi' 'BAR\\ $HOME /home/lgutter\\ \\g' \"BAR\\BAR\\ hoi' 'BAR\\ $HOME /home/lgutter\\ \\g\"/home/lgutter\\\\g";
	int		expected_ret = 0;
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	env_list->key = strdup("FOO");
	env_list->value = strdup("BAR\\");
	env_list->type = ENV_VAR;
	env_list->next = env_list2;
	env_list2->key = strdup("HOME");
	env_list2->value = strdup("/home/lgutter\\");
	env_list2->type = ENV_VAR;
	env_list2->next = NULL;
	shell.env = env_list;
	ret = process_word(&shell, &input, HEREDOCS_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", expected_ret, ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", expected_str, input);
}

Test(process_word_unit, valid_escaped_environment_expansion)
{
	char 	*input = strdup("\\$FOO");
	t_env	*env_list = (t_env *)malloc(sizeof(t_env) * 1);
	int		ret;
	char *	expected_str = "$FOO";
	int		expected_ret = 0;
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	env_list->key = strdup("FOO");
	env_list->value = strdup("hel\\lo");
	env_list->type = ENV_VAR;
	env_list->next = NULL;
	shell.env = env_list;
	ret = process_word(&shell, &input, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", expected_str, input);
}

Test(process_word_unit, invalid_NULL_input)
{
	char 	*input = NULL;
	int		ret;
	int		expected_ret = -1;

	ret = process_word(NULL, &input, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_eq(input, NULL);
}

Test(process_word_unit, invalid_NULL_input_pointer)
{
	int		ret;
	int		expected_ret = -1;

	ret = process_word(NULL, NULL, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
}

Test(process_word_unit, valid_expansion_NULL_env_list)
{
	char 	*input = strdup("foo$FOO");
	int		ret;
	char *	expected_str = "foo";
	int		expected_ret = 0;
	t_shell	shell;

	ft_bzero(&shell, sizeof(t_shell));
	ret = process_word(&shell, &input, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return %i but got %i!\n", ret, expected_ret);
	cr_assert_neq(input, NULL);
	cr_expect_str_eq(input, expected_str, "expected resulting string |%s|, but got |%s|\n", expected_str, input);
}
