/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_arguments.spec.c                             :+:    :+:            */
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

Test(parse_arguments_unit, valid_single_argument)
{
	t_argument *argument;


	t_token	*token1 = init_token(WORD, "foo", NULL);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	argument = parse_arguments(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, argument);
	cr_expect_eq(argument->next, NULL);
	cr_assert_neq(argument->argument, NULL);
	cr_expect_str_eq(argument->argument, "foo");
}

Test(parse_arguments_unit, valid_two_arguments)
{
	t_argument *argument;

	t_token	*token2 = init_token(WORD, "bar", NULL);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(WORD, "foo", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	argument = parse_arguments(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, argument);
	cr_assert_neq(argument->argument, NULL);
	cr_expect_str_eq(argument->argument, "foo");
	cr_assert_neq(argument->next, NULL);
	argument = argument->next;
	cr_assert_neq(argument->argument, NULL);
	cr_expect_str_eq(argument->argument, "bar");
	cr_expect_eq(argument->next, NULL);
}

Test(parse_arguments_unit, invalid_null_token, .init = redirect_std_err)
{
	t_argument *arguments;
	t_token			*token = NULL;

	arguments = parse_arguments(&token);
	cr_assert_eq(NULL, arguments);
	char buffer[1024];
	memset(buffer, 0, 1024);
	snprintf(buffer, 1024, "Cetushell: %s\n", g_error_str[invalid_token]);
	fflush(stderr);
	cr_expect_stderr_eq_str(buffer);
}

Test(parse_arguments_unit, invalid_null_token_pointer, .init = redirect_std_err)
{
	t_argument *arguments;

	arguments = parse_arguments(NULL);
	cr_assert_eq(NULL, arguments);
	char buffer[1024];
	memset(buffer, 0, 1024);
	snprintf(buffer, 1024, "Cetushell: %s\n", g_error_str[invalid_token]);
	fflush(stderr);
	cr_expect_stderr_eq_str(buffer);
}

Test(parse_arguments_unit, invalid_token_not_WORD, .init = redirect_std_err)
{
	t_argument *arguments;
	t_token		token = {IO_NUMBER, "42", NULL, NULL};
	t_token		*token_pointer = &token;

	arguments = parse_arguments(&token_pointer);
	cr_assert_eq(NULL, arguments);
	char buffer[1024];
	memset(buffer, 0, 1024);
	snprintf(buffer, 1024, "Cetushell: %s: 42\n", g_error_str[parsing_error]);
	fflush(stderr);
	cr_expect_stderr_eq_str(buffer);
}

Test(free_argument_unit, valid_free_two_arguments)
{
	t_argument *argument;

	t_token	*token2 = init_token(WORD, "foo", NULL);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(WORD, "bar", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	argument = parse_arguments(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, argument);

	free_arguments(argument);
}
