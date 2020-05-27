/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.spec.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 11:45:09 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/16 11:45:09 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "utils.h"

Test(check_quote_unit, valid_no_quotes)
{
	char *str = "foo bar test";
	int ret;

	ret = check_quote(str);
	cr_expect_eq(ret, 0, "expected: 0 | ret: %i", ret);
}

Test(check_quote_unit, valid_double_quote)
{
	char *str = "foo\"bar \"test";
	int ret;

	ret = check_quote(str);
	cr_expect_eq(ret, 2, "expected: 2 | ret: %i", ret);
}

Test(check_quote_unit, valid_empty_double_quote)
{
	char *str = "foo\"\"bar test";
	int ret;

	ret = check_quote(str);
	cr_expect_eq(ret, 2, "expected: 2 | ret: %i", ret);
}

Test(check_quote_unit, valid_single_quote)
{
	char *str = "foo\'bar \'test";
	int ret;

	ret = check_quote(str);
	cr_expect_eq(ret, 1, "expected: 1 | ret: %i", ret);
}

Test(check_quote_unit, valid_only_backslash)
{
	char *str = "foo bar \\test";
	int ret;

	ret = check_quote(str);
	cr_expect_eq(ret, 0, "expected: 0 | ret: %i", ret);
}

Test(check_quote_unit, invalid_unterminated_double_quote)
{
	char *str = "foo bar \"test";
	int ret;

	ret = check_quote(str);
	cr_expect_eq(ret, -2, "expected: -2 | ret: %i", ret);
}

Test(check_quote_unit, invalid_unterminated_single_quote)
{
	char *str = "foo bar \'test";
	int ret;

	ret = check_quote(str);
	cr_expect_eq(ret, -1, "expected: -1 | ret: %i", ret);
}

Test(check_quote_unit, invalid_backslash_unterminated_double_quote)
{
	char *str = "foo b\\\"ar \"test";
	int ret;

	ret = check_quote(str);
	cr_expect_eq(ret, -2, "expected: -2 | ret: %i", ret);
}

Test(check_quote_unit, invalid_backslash_unterminated_single_quote)
{
	char *str = "foo b\\\'ar \'test";
	int ret;

	ret = check_quote(str);
	cr_expect_eq(ret, -1, "expected: -1 | ret: %i", ret);
}

Test(check_quote_unit, invalid_unterminated_double_quote_backslash)
{
	char *str = "foo b\"ar \\\"test";
	int ret;

	ret = check_quote(str);
	cr_expect_eq(ret, -2, "expected: -2 | ret: %i", ret);
}

Test(check_quote_unit, valid_single_quote_containing_backslash)
{
	char *str = "foo bar \'tes\\\'t";
	int ret;

	ret = check_quote(str);
	cr_expect_eq(ret, 1, "expected: 1 | ret: %i", ret);
}

Test(check_quote_unit, valid_double_quote_containing_backslash)
{
	char *str = "foo bar \"te\\s\"t";
	int ret;

	ret = check_quote(str);
	cr_expect_eq(ret, 2, "expected: 2 | ret: %i", ret);
}

Test(check_quote_unit, valid_double_quote_containing_escaped_d_quote)
{
	char *str = "foo bar \"tes\\\"\"t";
	int ret;

	ret = check_quote(str);
	cr_expect_eq(ret, 2, "expected: 2 | ret: %i", ret);
}

Test(check_quote_unit, invalid_NULL_string)
{
	char *str = NULL;
	int ret;

	ret = check_quote(str);
	cr_expect_eq(ret, -1, "expected: -1 | ret: %i", ret);
}

Test(remove_quotes_unit, valid_no_quotes)
{
	char *str		= strdup("hello foo bar");
	char *expected	= "hello foo bar";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, valid_double_quote)
{
	char *str		= strdup("hel\"lo foo b\"ar");
	char *expected	= "hello foo bar";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, valid_empty_double_quote)
{
	char *str		= strdup("hel\"\"lo foo bar");
	char *expected	= "hello foo bar";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, valid_only_escaped_double_quote_in_double_quote)
{
	char *str		= strdup("hel\"\\\"\"lo foo bar");
	char *expected	= "hel\"lo foo bar";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, valid_only_escaped_newline_in_double_quote)
{
	char *str		= strdup("hel\"\\\n\"lo foo bar");
	char *expected	= "hello foo bar";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, valid_only_escaped_dollar_in_double_quote)
{
	char *str		= strdup("hel\"\\$\"lo foo bar");
	char *expected	= "hel$lo foo bar";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, valid_only_escaped_normal_char_in_double_quote)
{
	char *str		= strdup("hel\"\\n\"lo foo bar");
	char *expected	= "hel\\nlo foo bar";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, valid_single_quote)
{
	char *str		= strdup("\'hello foo b\'ar");
	char *expected	= "hello foo bar";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, valid_single_quote_containing_backslash)
{
	char *str		= strdup("\'hello f\\oo b\'ar");
	char *expected	= "hello f\\oo bar";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, valid_single_quote_containing_backslash_at_start)
{
	char *str		= strdup("\'\\hello foo b\'ar");
	char *expected	= "\\hello foo bar";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, valid_single_quote_containing_backslash_at_end)
{
	char *str		= strdup("\'hello foo b\\\'ar");
	char *expected	= "hello foo b\\ar";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, valid_single_quote_containing_double_quote_char)
{
	char *str		= strdup("\'hello foo bar\"\'");
	char *expected	= "hello foo bar\"";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, valid_double_quote_containing_backslash)
{
	char *str		= strdup("\"hello f\\oo b\"ar");
	char *expected	= "hello f\\oo bar";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, valid_double_quote_containing_single_quote_char)
{
	char *str		= strdup("\"hello foo \'bar\"");
	char *expected	= "hello foo \'bar";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, valid_double_quote_escaped_double_quote)
{
	char *str		= strdup("\"hello foo b\\\"\"ar");
	char *expected	= "hello foo b\"ar";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, valid_double_quote_escaped_double_quote_in_heredoc)
{
	char *str		= strdup("\"hello foo b\\\"\"ar");
	char *expected	= "\"hello foo b\\\"\"ar";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, HEREDOCS_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, valid_double_quote_escaped_newline_in_heredoc)
{
	char *str		= strdup("\"hello foo b\\\n\"ar");
	char *expected	= "\"hello foo b\"ar";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, HEREDOCS_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, valid_multiple_backslashes)
{
	char *str		= strdup("\\hello f\\\\oo b\\ar\\");
	char *expected	= "hello f\\oo bar";
	int ret;
	int expected_ret = 0;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, invalid_unterminated_double_quote)
{
	char *str		= strdup("\"hello foo bar");
	char *expected	= "\"hello foo bar";
	int ret;
	int expected_ret = -1;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, invalid_unterminated_single_quote)
{
	char *str		= strdup("\'hello foo bar");
	char *expected	= "\'hello foo bar";
	int ret;
	int expected_ret = -1;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_neq(str, NULL, "malloc failed!");
	cr_expect_str_eq(str, expected, "expected string |%s|, got |%s|.", expected, str);
}

Test(remove_quotes_unit, invalid_NULL_string)
{
	char *str		= NULL;
	int ret;
	int expected_ret = -1;

	ret = remove_quotes(&str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %i, got %i.", expected_ret, ret);
	cr_assert_eq(str, NULL);
}

Test(count_quote_chars_unit, valid_no_qoutes)
{
	char *str		= "no quotes here!";
	size_t ret;
	size_t expected_ret = 0;

	ret = count_quote_chars(str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %zu, got %zu.", expected_ret, ret);
}

Test(count_quote_chars_unit, valid_double_qoute)
{
	char *str		= "\"double quote \"here!";
	size_t ret;
	size_t expected_ret = 2;

	ret = count_quote_chars(str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %zu, got %zu.", expected_ret, ret);
}

Test(count_quote_chars_unit, valid_empty_double_qoute)
{
	char *str		= "\"\"double quote here!";
	size_t ret;
	size_t expected_ret = 2;

	ret = count_quote_chars(str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %zu, got %zu.", expected_ret, ret);
}

Test(count_quote_chars_unit, valid_single_qoute)
{
	char *str		= "\'single quote \'here!";
	size_t ret;
	size_t expected_ret = 2;

	ret = count_quote_chars(str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %zu, got %zu.", expected_ret, ret);
}

Test(count_quote_chars_unit, valid_single_qoute_containing_backslash)
{
	char *str		= "\'single quot\\e \'here!";
	size_t ret;
	size_t expected_ret = 2;

	ret = count_quote_chars(str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %zu, got %zu.", expected_ret, ret);
}

Test(count_quote_chars_unit, valid_single_qoute_containing_backslash_in_heredoc)
{
	char *str		= "\'single quot\\e \'here!";
	size_t ret;
	size_t expected_ret = 0;

	ret = count_quote_chars(str, HEREDOCS_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %zu, got %zu.", expected_ret, ret);
}

Test(count_quote_chars_unit, valid_single_qoute_containing_double_quote_char)
{
	char *str		= "\'single quote here!\"\'";
	size_t ret;
	size_t expected_ret = 2;

	ret = count_quote_chars(str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %zu, got %zu.", expected_ret, ret);
}

Test(count_quote_chars_unit, valid_double_qoute_containing_backslash)
{
	char *str		= "\"double quot\\e \"here!";
	size_t ret;
	size_t expected_ret = 2;

	ret = count_quote_chars(str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %zu, got %zu.", expected_ret, ret);
}

Test(count_quote_chars_unit, valid_double_qoute_containing_singe_quote_char)
{
	char *str		= "\"double quote here!\'\"";
	size_t ret;
	size_t expected_ret = 2;

	ret = count_quote_chars(str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %zu, got %zu.", expected_ret, ret);
}

Test(count_quote_chars_unit, valid_double_qoute_containing_escaped_double_quote)
{
	char *str		= "\"double quot\\\"e \"here!";
	size_t ret;
	size_t expected_ret = 3;

	ret = count_quote_chars(str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %zu, got %zu.", expected_ret, ret);
}

Test(count_quote_chars_unit, valid_double_qoute_containing_escaped_newline_in_heredoc)
{
	char *str		= "\"double quot\\\ne \"here!";
	size_t ret;
	size_t expected_ret = 2;

	ret = count_quote_chars(str, HEREDOCS_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %zu, got %zu.", expected_ret, ret);
}

Test(count_quote_chars_unit, valid_double_qoute_containing_escaped_single_quote)
{
	char *str		= "\"double quot\\\'e \"here!";
	size_t ret;
	size_t expected_ret = 2;

	ret = count_quote_chars(str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %zu, got %zu.", expected_ret, ret);
}

Test(count_quote_chars_unit, valid_single_qoute_containing_escaped_double_quote)
{
	char *str		= "\'single quot\\\"e \'here!";
	size_t ret;
	size_t expected_ret = 2;

	ret = count_quote_chars(str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %zu, got %zu.", expected_ret, ret);
}

Test(count_quote_chars_unit, valid_multiple_backslashes)
{
	char *str		= "\\backslash\\\\es \\here!\\";
	size_t ret;
	size_t expected_ret = 4;

	ret = count_quote_chars(str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %zu, got %zu.", expected_ret, ret);
}

Test(count_quote_chars_unit, invalid_NULL_string)
{
	char *str		= NULL;
	size_t ret;
	size_t expected_ret = -1;

	ret = count_quote_chars(str, ALL_QUOTES_TABLE);
	cr_expect_eq(ret, expected_ret, "expected return value %zu, got %zu.", expected_ret, ret);
}

Test(backslash_quotes_unit, valid_no_quotes)
{
	char *str		= "hello foo bar";
	char *expected	= "hello foo bar";
	char *ret;

	ret = backslash_quotes(str);
	cr_assert_neq(ret, NULL, "malloc failed!");
	cr_expect_str_eq(ret, expected, "expected string |%s|, got |%s|.", expected, ret);
}

Test(backslash_quotes_unit, valid_double_quote)
{
	char *str		= "hel\"lo foo b\"ar";
	char *expected	= "hel\\\"lo foo b\\\"ar";
	char *ret;

	ret = backslash_quotes(str);
	cr_assert_neq(ret, NULL, "malloc failed!");
	cr_expect_str_eq(ret, expected, "expected string |%s|, got |%s|.", expected, ret);
}

Test(backslash_quotes_unit, valid_empty_double_quote)
{
	char *str		= "hel\"\"lo foo bar";
	char *expected	= "hel\\\"\\\"lo foo bar";
	char *ret;

	ret = backslash_quotes(str);
	cr_assert_neq(ret, NULL, "malloc failed!");
	cr_expect_str_eq(ret, expected, "expected string |%s|, got |%s|.", expected, ret);
}

Test(backslash_quotes_unit, valid_single_quote)
{
	char *str		= "hel\'lo foo b\'ar";
	char *expected	= "hel\\\'lo foo b\\\'ar";
	char *ret;

	ret = backslash_quotes(str);
	cr_assert_neq(ret, NULL, "malloc failed!");
	cr_expect_str_eq(ret, expected, "expected string |%s|, got |%s|.", expected, ret);
}

Test(backslash_quotes_unit, valid_single_backslash)
{
	char *str		= "hel\\lo foo bar";
	char *expected	= "hel\\\\lo foo bar";
	char *ret;

	ret = backslash_quotes(str);
	cr_assert_neq(ret, NULL, "malloc failed!");
	cr_expect_str_eq(ret, expected, "expected string |%s|, got |%s|.", expected, ret);
}

Test(backslash_quotes_unit, valid_unterminated_double_quote)
{
	char *str		= "hel\"lo foo bar";
	char *expected	= "hel\\\"lo foo bar";
	char *ret;

	ret = backslash_quotes(str);
	cr_assert_neq(ret, NULL, "malloc failed!");
	cr_expect_str_eq(ret, expected, "expected string |%s|, got |%s|.", expected, ret);
}

Test(backslash_quotes_unit, valid_unterminated_single_quote)
{
	char *str		= "hel\'lo foo bar";
	char *expected	= "hel\\\'lo foo bar";
	char *ret;

	ret = backslash_quotes(str);
	cr_assert_neq(ret, NULL, "malloc failed!");
	cr_expect_str_eq(ret, expected, "expected string |%s|, got |%s|.", expected, ret);
}

Test(backslash_quotes_unit, valid_unterminated_single_quote_backslash)
{
	char *str		= "hel\\\'lo \'foo bar";
	char *expected	= "hel\\\\\\\'lo \\\'foo bar";
	char *ret;

	ret = backslash_quotes(str);
	cr_assert_neq(ret, NULL, "malloc failed!");
	cr_expect_str_eq(ret, expected, "expected string |%s|, got |%s|.", expected, ret);
}

Test(backslash_quotes_unit, valid_unterminated_double_quote_backslash)
{
	char *str		= "hel\\\"lo \"foo bar";
	char *expected	= "hel\\\\\\\"lo \\\"foo bar";
	char *ret;

	ret = backslash_quotes(str);
	cr_assert_neq(ret, NULL, "malloc failed!");
	cr_expect_str_eq(ret, expected, "expected string |%s|, got |%s|.", expected, ret);
}

Test(backslash_quotes_unit, valid_unterminated_double_quote_backslash_end)
{
	char *str		= "hel\"lo \\\"foo bar";
	char *expected	= "hel\\\"lo \\\\\\\"foo bar";
	char *ret;

	ret = backslash_quotes(str);
	cr_assert_neq(ret, NULL, "malloc failed!");
	cr_expect_str_eq(ret, expected, "expected string |%s|, got |%s|.", expected, ret);
}

Test(backslash_quotes_unit, valid_unterminated_double_quote_single_quote_end)
{
	char *str		= "hel\"lo \'foo bar";
	char *expected	= "hel\\\"lo \\\'foo bar";
	char *ret;

	ret = backslash_quotes(str);
	cr_assert_neq(ret, NULL, "malloc failed!");
	cr_expect_str_eq(ret, expected, "expected string |%s|, got |%s|.", expected, ret);
}

Test(backslash_quotes_unit, valid_unterminated_single_quote_double_quote_end)
{
	char *str		= "hel\'lo \"foo bar";
	char *expected	= "hel\\\'lo \\\"foo bar";
	char *ret;

	ret = backslash_quotes(str);
	cr_assert_neq(ret, NULL, "malloc failed!");
	cr_expect_str_eq(ret, expected, "expected string |%s|, got |%s|.", expected, ret);
}

Test(backslash_quotes_unit, valid_single_quote_containing_double_quote)
{
	char *str		= "hel\'lo \"foo bar\'";
	char *expected	= "hel\\\'lo \\\"foo bar\\\'";
	char *ret;

	ret = backslash_quotes(str);
	cr_assert_neq(ret, NULL, "malloc failed!");
	cr_expect_str_eq(ret, expected, "expected string |%s|, got |%s|.", expected, ret);
}

Test(backslash_quotes_unit, valid_double_quote_containing_single_quote)
{
	char *str		= "hel\"lo \'foo bar\"";
	char *expected	= "hel\\\"lo \\\'foo bar\\\"";
	char *ret;

	ret = backslash_quotes(str);
	cr_assert_neq(ret, NULL, "malloc failed!");
	cr_expect_str_eq(ret, expected, "expected string |%s|, got |%s|.", expected, ret);
}

Test(backslash_quotes_unit, valid_multiple_backslashes)
{
	char *str		= "\\hel\\lo \\foo bar\\";
	char *expected	= "\\\\hel\\\\lo \\\\foo bar\\\\";
	char *ret;

	ret = backslash_quotes(str);
	cr_assert_neq(ret, NULL, "malloc failed!");
	cr_expect_str_eq(ret, expected, "expected string |%s|, got |%s|.", expected, ret);
}

Test(backslash_quotes_unit, invalid_NULL_string)
{
	char *str		= NULL;
	char *ret;

	ret = backslash_quotes(str);
	cr_assert_eq(ret, NULL);
}
