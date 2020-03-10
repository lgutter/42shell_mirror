/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_terminal.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 12:24:22 by dkroeke        #+#    #+#                */
/*   Updated: 2020/02/12 12:24:22 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "tokenizer.h"

Test(tokenizer_tests, basic_mandatory_no_tokens)
{
	t_token *result = NULL;

	result = tokenizer("");
	cr_expect_eq(result, NULL);
}

Test(tokenizer_tests, basic_mandatory_extra_blanks_no_tokens)
{
	t_token *result = NULL;

	result = tokenizer("  		 	");
	cr_expect_eq(result, NULL);
}

Test(tokenizer_tests, basic_mandatory_one_word_token)
{
	t_token *result = NULL;

	result = tokenizer("7oo");
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "7oo");
}

Test(tokenizer_tests, basic_mandatory_one_word_token_extra_blanks)
{
	t_token *result = NULL;

	result = tokenizer("  		  7oo			  ");
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "7oo");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_one_word_token_dquote)
{
	t_token *result = NULL;

	result = tokenizer("\"author';foo'\"");
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "\"author';foo'\"");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_one_word_token_dquote_continued)
{
	t_token *result = NULL;

	result = tokenizer("foo\"bar\"baz");
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "foo\"bar\"baz");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_one_word_token_squote_continued)
{
	t_token *result = NULL;

	result = tokenizer("foo'bar'baz");
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "foo'bar'baz");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_one_word_token_squote_everything)
{
	t_token *result = NULL;

	result = tokenizer("		 '&>&<;|\n\"2<&	 \\'  ");
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "'&>&<;|\n\"2<&	 \\'");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_one_word_token_dquote_everything)
{
	t_token *result = NULL;

	result = tokenizer("	 \"&>&<;|\n\\\"2<&	 \\\"\" 	 ");
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "\"&>&<;|\n\\\"2<&	 \\\"\"");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_three_tokens_word_semi_word)
{
	t_token *result = NULL;

	result = tokenizer("\\\"\\ ;\\;");
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "\\\"\\ ");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, SEMI);
	cr_expect_str_eq(result->value, ";");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "\\;");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_two_word_tokens_extra_blanks)
{
	t_token *result = NULL;

	result = tokenizer("  		  7oo		foo42	  ");
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "7oo");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "foo42");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_two_word_tokens_with_punctuation)
{
	t_token *result = NULL;

	result = tokenizer("ca,t meson.build");
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "ca,t");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "meson.build");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_four_tokens_word_io_number_lessamp_word)
{
	t_token *result = NULL;

	result = tokenizer("7oo		42>&2");
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "7oo");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, IO_NUMBER);
	cr_expect_str_eq(result->value, "42");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, GREATAMP);
	cr_expect_str_eq(result->value, ">&");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "2");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_four_tokens_word_dless_lessamp_great)
{
	t_token *result = NULL;

	result = tokenizer("7oo		<<<&>");
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "7oo");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, DLESS);
	cr_expect_str_eq(result->value, "<<");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, LESSAMP);
	cr_expect_str_eq(result->value, "<&");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, GREAT);
	cr_expect_str_eq(result->value, ">");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_four_tokens_word_pipe_squote_amp)
{
	t_token *result = NULL;

	result = tokenizer("echo|'\\$(CC)' &");
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "echo");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, PIPE);
	cr_expect_str_eq(result->value, "|");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "'\\$(CC)'");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, AMP);
	cr_expect_str_eq(result->value, "&");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_four_tokens_word_word_semi_word)
{
	t_token *result = NULL;

	result = tokenizer("echo $PWD;	 foo");
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "echo");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "$PWD");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, SEMI);
	cr_expect_str_eq(result->value, ";");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "foo");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, edge_case_mandatory_buffer_expansion, .timeout = 30)
{
	t_token	*result = NULL;
	char	*longstr;

	longstr = malloc(BUFFER_SIZE + 43);
	ft_memset(longstr, 'a', BUFFER_SIZE + 42);
	longstr[BUFFER_SIZE + 42] = '\0';
	result = tokenizer(longstr);
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, longstr);
}

Test(tokenizer_tests, edge_case_mandatory_extra_blanks_null_term_no_tokens)
{
	t_token *result = NULL;

	result = tokenizer("  	\0	 foo	");
	cr_expect_eq(result, NULL);
}
