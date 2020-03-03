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

Test(tokenizer, basic_mandatory_no_tokens)
{
	t_token *result = NULL;

	result = tokenizer("");
	cr_expect_eq(result, NULL);
}

Test(tokenizer, basic_mandatory_one_word_token)
{
	t_token *result = NULL;

	result = tokenizer("7oo");
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "7oo");
}

Test(tokenizer, basic_mandatory_one_word_token_extra_blanks)
{
	t_token *result = NULL;

	result = tokenizer("  		  7oo			  ");
	cr_assert_neq(result, NULL);
	cr_expect_eq(result->type, WORD);
	cr_expect_str_eq(result->value, "7oo");
	cr_expect_eq(result->next, NULL);
}

Test(tokenizer, basic_mandatory_two_word_tokens_extra_blanks)
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

Test(tokenizer, basic_mandatory_four_tokens_word_io_number_lessamp_word)
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

Test(tokenizer, basic_mandatory_four_tokens_word_dless_lessamp_great)
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
