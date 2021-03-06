/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.spec.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 12:24:22 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/02/12 12:24:22 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "tokenizer.h"

Test(tokenizer_tests, basic_mandatory_no_tokens)
{
	t_token *result = NULL;
	char 	*input = "";

	result = tokenizer(NULL, &input);
	cr_expect_eq(result, NULL);
}

Test(tokenizer_tests, basic_mandatory_extra_blanks_no_tokens)
{
	t_token *result = NULL;
	char 	*input = "  		 	";

	result = tokenizer(NULL, &input);
	cr_expect_eq(result, NULL);
}

Test(tokenizer_tests, basic_mandatory_one_word_token)
{
	t_token *result = NULL;
	char 	*input = "7oo";

	result = tokenizer(NULL, &input);
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "7oo");
}

Test(tokenizer_tests, basic_mandatory_one_word_token_extra_blanks)
{
	t_token *result = NULL;
	char 	*input = "  		  7oo			  ";

	result = tokenizer(NULL, &input);
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "7oo");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_one_word_token_dquote)
{
	t_token *result = NULL;
	char 	*input = "\"author';foo'\"";

	result = tokenizer(NULL, &input);
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "\"author';foo'\"");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_one_word_token_dquote_continued)
{
	t_token *result = NULL;
	char 	*input = "foo\"bar\"baz";

	result = tokenizer(NULL, &input);
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "foo\"bar\"baz");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_one_word_token_squote_continued)
{
	t_token *result = NULL;
	char 	*input = "foo'bar'baz";

	result = tokenizer(NULL, &input);
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "foo'bar'baz");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_one_word_token_squote_everything)
{
	t_token *result = NULL;
	char 	*input = "		 '&>&<;|\n\"2<&	 \\'  ";

	result = tokenizer(NULL, &input);
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "'&>&<;|\n\"2<&	 \\'");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_one_word_token_dquote_everything)
{
	t_token *result = NULL;
	char 	*input = "	 \"&>&<;|\n\\\"2<&	 \\\"\" 	 ";

	result = tokenizer(NULL, &input);
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "\"&>&<;|\n\\\"2<&	 \\\"\"");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_three_tokens_word_semi_word)
{
	t_token *result = NULL;
	char 	*input = "\\\"\\ ;\\;";

	result = tokenizer(NULL, &input);
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
	char 	*input = "  		  7oo		foo42	  ";

	result = tokenizer(NULL, &input);
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
	char 	*input = "ca,t meson.build";

	result = tokenizer(NULL, &input);
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
	char 	*input = "7oo		42>&2";

	result = tokenizer(NULL, &input);
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
	char 	*input = "7oo		<<<&>";

	result = tokenizer(NULL, &input);
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

Test(tokenizer_tests, basic_mandatory_four_tokens_word_dgreat_greatamp_less)
{
	t_token *result = NULL;
	char 	*input = "7oo		>>>&<";

	result = tokenizer(NULL, &input);
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "7oo");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, DGREAT);
	cr_expect_str_eq(result->value, ">>");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, GREATAMP);
	cr_expect_str_eq(result->value, ">&");
	result = result->next;
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, LESS);
	cr_expect_str_eq(result->value, "<");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_mandatory_four_tokens_word_pipe_squote_amp)
{
	t_token *result = NULL;
	char 	*input = "echo|'\\$(CC)' &";

	result = tokenizer(NULL, &input);
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

Test(tokenizer_tests, basic_mandatory_four_tokens_newline_word_semi_word)
{
	t_token *result = NULL;
	char 	*input = "\n $PWD;	 foo";

	result = tokenizer(NULL, &input);
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, NEWLINE);
	cr_expect_str_eq(result->value, "\n");
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

Test(tokenizer_tests, edge_case_mandatory_buffer_expansion)
{
	t_token	*result = NULL;
	char	*longstr;

	longstr = ft_memalloc(TOKEN_BUFF_SIZE + 43);
	ft_memset(longstr, 'a', TOKEN_BUFF_SIZE + 42);
	result = tokenizer(NULL, &longstr);
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, longstr);
}

Test(tokenizer_tests, edge_case_mandatory_extra_blanks_null_term_no_tokens)
{
	t_token *result = NULL;
	char 	*input = "  	\0	 foo	";

	result = tokenizer(NULL, &input);
	cr_expect_eq(result, NULL);
}

Test(tokenizer_tests, basic_mandatory_error_NULL_input)
{
	t_token *result = NULL;
	char 	*input = NULL;

	result = tokenizer(NULL, &input);
	cr_expect_eq(result, NULL);
}

Test(tokenizer_tests, basic_mandatory_error_NULL_input_pointer)
{
	t_token *result = NULL;

	result = tokenizer(NULL, NULL);
	cr_expect_eq(result, NULL);
}

Test(tokenizer_tests, basic_command_substitution)
{
	t_token *result = NULL;
	char 	*input = "$(ls -al)";

	result = tokenizer(NULL, &input);
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "$(ls -al)");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_command_substitution_double_quoted)
{
	t_token *result = NULL;
	char 	*input = "\"$(ls -al)\"";

	result = tokenizer(NULL, &input);
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "\"$(ls -al)\"");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer_tests, basic_command_substitution_double_quote_nested)
{
	t_token *result = NULL;
	char 	*input = "\"$(ls -al \"folder with spaces\")\"";

	result = tokenizer(NULL, &input);
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "\"$(ls -al \"folder with spaces\")\"");
	cr_expect_eq(result->next, NULL);
}
