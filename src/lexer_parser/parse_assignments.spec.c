/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_assignments.spec.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/10 13:17:43 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/10 13:17:43 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "tokenizer.h"
#include "parser.h"
#include "error_str.h"

static void redirect_std_err(void)
{
	cr_redirect_stderr();
}

static t_token	*init_token(t_type type, const char *value, t_token *next)
{
	t_token *token = (t_token *)malloc(sizeof(t_token) * 1);
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->value = strdup(value);
	if (token->value == NULL)
	{
		free(token);
		return (NULL);
	}
	token->next = next;
	return (token);
}

Test(parse_assignments_unit, valid_single_assignment)
{
	t_assignment *assignment;


	t_token	*token1 = init_token(WORD, "foo=bar", NULL);
	cr_assert_not_null(token1, "malloc failed!");
	t_token *tokens = token1;

	assignment = parse_assignments(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_not_null(assignment);
	cr_expect_eq(assignment->next, NULL);
	cr_assert_not_null(assignment->key);
	cr_expect_str_eq(assignment->key, "foo");
	cr_expect_str_eq(assignment->value, "bar");
}

Test(parse_assignments_unit, valid_two_assignments)
{
	t_assignment *assignment;

	t_token	*token2 = init_token(WORD, "bar=foo", NULL);
	cr_assert_not_null(token2, "malloc failed!");
	t_token	*token1 = init_token(WORD, "foo=bar", token2);
	cr_assert_not_null(token1, "malloc failed!");
	t_token *tokens = token1;

	assignment = parse_assignments(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_not_null(assignment);
	cr_assert_not_null(assignment->key);
	cr_expect_str_eq(assignment->key, "foo");
	cr_expect_str_eq(assignment->value, "bar");
	cr_assert_neq(assignment->next, NULL);
	assignment = assignment->next;
	cr_assert_not_null(assignment->key);
	cr_expect_str_eq(assignment->key, "bar");
	cr_expect_str_eq(assignment->value, "foo");
	cr_expect_eq(assignment->next, NULL);
}

Test(parse_assignments_unit, invalid_null_token, .init = redirect_std_err)
{
	t_assignment *assignments;
	t_token			*token = NULL;

	assignments = parse_assignments(&token);
	cr_assert_eq(NULL, assignments);
	char buffer[1024];
	memset(buffer, 0, 1024);
	snprintf(buffer, 1024, "Cetushell: %s\n", g_error_str[invalid_token]);
	fflush(stderr);
	cr_expect_stderr_eq_str(buffer);
}

Test(parse_assignments_unit, invalid_null_token_pointer, .init = redirect_std_err)
{
	t_assignment *assignments;

	assignments = parse_assignments(NULL);
	cr_assert_eq(NULL, assignments);
	char buffer[1024];
	memset(buffer, 0, 1024);
	snprintf(buffer, 1024, "Cetushell: %s\n", g_error_str[invalid_token]);
	fflush(stderr);
	cr_expect_stderr_eq_str(buffer);
}

Test(parse_assignments_unit, invalid_token_not_WORD, .init = redirect_std_err)
{
	t_assignment *assignments;
	t_token		token = {IO_NUMBER, "42", NULL};
	t_token		*token_pointer = &token;

	assignments = parse_assignments(&token_pointer);
	cr_assert_eq(NULL, assignments);
	char buffer[1024];
	memset(buffer, 0, 1024);
	snprintf(buffer, 1024, "Cetushell: %s: 42\n", g_error_str[parsing_error]);
	fflush(stderr);
	cr_expect_stderr_eq_str(buffer);
}

Test(free_assignment_unit, valid_free_two_assignments)
{
	t_assignment *assignment;

	t_token	*token2 = init_token(WORD, "foo=bar", NULL);
	cr_assert_not_null(token2, "malloc failed!");
	t_token	*token1 = init_token(WORD, "bar=foo", token2);
	cr_assert_not_null(token1, "malloc failed!");
	t_token *tokens = token1;

	assignment = parse_assignments(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_not_null(assignment);

	free_assignments(assignment);
}
