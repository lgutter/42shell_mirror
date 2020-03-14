/* ************************************************************************** */
/*                                                                            */
/*   cetushell - 21 Shell                                 ::::::::            */
/*                                                      :+:    :+:            */
/*   By: dkroeke <dkroeke@student.codam.nl>            +:+                    */
/*       lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*                                                 #+#    #+#                 */
/*   License: GPLv3                                ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "tokenizer.h"

Test(free_token_list_tests, free_short_simple_list)
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
	cr_expect_eq(start, NULL);
}
