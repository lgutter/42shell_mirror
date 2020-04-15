/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_io_here.spec.c                           :+:    :+:            */
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

Test(parse_io_here_unit, valid_here_doc)
{
	t_io_here *io_here;

	t_token	*token2 = init_token(WORD, "EOF", NULL);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DLESS, "<<", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	io_here = parse_io_here(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, io_here);
	cr_assert_neq(NULL, io_here->here_end);
	cr_expect_str_eq(io_here->here_end, "EOF");
}

Test(parse_io_here_unit, invalid_null_token, .init = redirect_std_err)
{
	t_io_here *io_here;
	t_token			*token = NULL;

	io_here = parse_io_here(&token);
	cr_assert_eq(NULL, io_here);
}

Test(parse_io_here_unit, invalid_null_token_pointer, .init = redirect_std_err)
{
	t_io_here *io_here;

	io_here = parse_io_here(NULL);
	cr_assert_eq(NULL, io_here);
}

Test(free_io_here_unit, valid_free_here_doc)
{
	t_io_here *io_here;

	t_token	*token2 = init_token(WORD, "EOF", NULL);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DLESS, "<<", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	io_here = parse_io_here(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, io_here);

	free_io_here(io_here);
}
