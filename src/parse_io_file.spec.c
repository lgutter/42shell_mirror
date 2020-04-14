/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_io_file.spec.c                           :+:    :+:            */
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

Test(parse_io_file_unit, valid_file_redirect_in)
{
	t_io_file *io_file;

	t_token	*token2 = init_token(WORD, "foo", NULL);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(LESS, "<", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	io_file = parse_io_file(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, io_file);
	cr_expect_eq(io_file->redirect_op, redirect_in);
	cr_assert_neq(NULL, io_file->filename);
	cr_expect_str_eq(io_file->filename, "foo");
}

Test(parse_io_file_unit, valid_file_redirect_out)
{
	t_io_file *io_file;

	t_token	*token2 = init_token(WORD, "foo", NULL);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(GREAT, ">", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	io_file = parse_io_file(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, io_file);
	cr_expect_eq(io_file->redirect_op, redirect_out);
	cr_assert_neq(NULL, io_file->filename);
	cr_expect_str_eq(io_file->filename, "foo");
}

Test(parse_io_file_unit, valid_file_redirect_append)
{
	t_io_file *io_file;

	t_token	*token2 = init_token(WORD, "foo", NULL);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DGREAT, ">>", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	io_file = parse_io_file(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, io_file);
	cr_expect_eq(io_file->redirect_op, redirect_append);
	cr_assert_neq(NULL, io_file->filename);
	cr_expect_str_eq(io_file->filename, "foo");
}

Test(parse_io_file_unit, valid_file_redirect_fd_in)
{
	t_io_file *io_file;

	t_token	*token2 = init_token(WORD, "42", NULL);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(LESSAMP, "<&", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	io_file = parse_io_file(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, io_file);
	cr_expect_eq(io_file->redirect_op, redirect_fd_in);
	cr_assert_neq(NULL, io_file->filename);
	cr_expect_str_eq(io_file->filename, "42");
}

Test(parse_io_file_unit, valid_file_redirect_fd_out)
{
	t_io_file *io_file;

	t_token	*token2 = init_token(WORD, "42", NULL);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(GREATAMP, ">&", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	io_file = parse_io_file(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, io_file);
	cr_expect_eq(io_file->redirect_op, redirect_fd_out);
	cr_assert_neq(NULL, io_file->filename);
	cr_expect_str_eq(io_file->filename, "42");
}

Test(parse_io_file_unit, invalid_null_token)
{
	t_io_file *io_file;
	t_token			*token = NULL;

	io_file = parse_io_file(&token);
	cr_assert_eq(NULL, io_file);
}

Test(parse_io_file_unit, invalid_null_token_pointer)
{
	t_io_file *io_file;

	io_file = parse_io_file(NULL);
	cr_assert_eq(NULL, io_file);
}

Test(free_io_file_unit, valid_free_file_redirect_append)
{
	t_io_file *io_file;

	t_token	*token2 = init_token(WORD, "foo", NULL);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DGREAT, ">>", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	io_file = parse_io_file(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, io_file);

	free_io_file(io_file);
}
