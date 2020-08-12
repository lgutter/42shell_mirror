/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list_util.spec.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: Invalid date        by               #+#    #+#                 */
/*   Updated: 0003/01/01 00:00:00 by               ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "tokenizer.h"

Test(free_token_list_test, free_short_simple_list)
{
	t_token *node1 = malloc(sizeof(t_token));
	t_token *node2 = malloc(sizeof(t_token));
	t_token *node3 = malloc(sizeof(t_token));
	cr_assert_neq(node1, NULL, "malloc failed!");
	cr_assert_neq(node2, NULL, "malloc failed!");
	cr_assert_neq(node3, NULL, "malloc failed!");
	t_token *start = node1;

	node1->type = WORD;
	node1->value = strdup("foo");
	node1->next = node2;
	node1->type = DLESS;
	node2->value = strdup("<<");
	node2->next = node3;
	node1->type = IO_NUMBER;
	node3->value = strdup("42");
	node3->next = NULL;
	free_token_list(&start);
	cr_expect_eq(start, NULL, "list start was not set to NULL!");
}

Test(free_token_list_test, invalid_NULL_list)
{
	t_token *list = NULL;
	t_token *ret;

	ret = free_token_list(&list);
	cr_expect_eq(ret, NULL);
}

Test(free_token_list_test, invalid_NULL_list_p)
{
	t_token *ret;

	ret = free_token_list(NULL);
	cr_expect_eq(ret, NULL);
}

Test(add_token_tests, add_single_token)
{
	t_token *start = NULL;
	t_vecstr buffer;
	int ret;

	buffer = new_vecstr("foobarbaz");
	cr_assert_not_null(buffer.string, "malloc failed!");
	ret = add_token(&start, WORD, &buffer);
	cr_expect_eq(ret, 0);
	cr_assert_neq(NULL, start);
	cr_expect_eq(NULL, start->next);
	cr_expect_str_eq(start->value, "foobarbaz");
	cr_assert_null(buffer.string);
	cr_assert_eq(buffer.len, 0);
	cr_assert_eq(buffer.cap, 0);
}

Test(add_token_tests, add_three_tokens_to_empty_list)
{
	t_token *start = NULL;
	char *strings[3] = {
		"foo",
		"bar",
		"baz"
	};
	t_vecstr buffer;
	int ret;
	int i = 0;

	while (i < 3)
	{
		buffer = new_vecstr(strings[i]);
		cr_assert_not_null(buffer.string, "malloc failed!");
		ret = add_token(&start, WORD, &buffer);
		cr_expect_eq(ret, 0);
		cr_assert_null(buffer.string);
		cr_assert_eq(buffer.len, 0);
		cr_assert_eq(buffer.cap, 0);
		i++;
	}
	cr_assert_neq(NULL, start);
	cr_expect_str_eq(start->value, strings[0]);
	cr_assert_neq(NULL, start->next);
	start = start->next;
	cr_assert_neq(NULL, start);
	cr_expect_str_eq(start->value, strings[1]);
	cr_assert_neq(NULL, start->next);
	start = start->next;
	cr_assert_neq(NULL, start);
	cr_expect_str_eq(start->value, strings[2]);
	cr_expect_eq(NULL, start->next);
}

Test(add_token_tests, invalid_NULL_start)
{
	t_vecstr buffer;
	int ret;

	buffer = new_vecstr("foobarbaz");
	cr_assert_not_null(buffer.string, "malloc failed!");
	ret = add_token(NULL, WORD, &buffer);
	cr_expect_eq(ret, -1);
	cr_assert_str_eq(buffer.string, "foobarbaz");
	cr_assert_eq(buffer.len, 9);
	cr_assert(buffer.cap > 9);
}

Test(add_token_tests, invalid_NULL_buffer)
{
	t_token *start = NULL;
	int ret;

	ret = add_token(&start, WORD, NULL);
	cr_expect_eq(ret, -1);
	cr_expect_eq(start, NULL);
}
