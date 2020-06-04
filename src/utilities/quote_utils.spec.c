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
