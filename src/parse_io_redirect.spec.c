/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_io_redirect.spec.c                           :+:    :+:            */
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

Test(parse_io_redirect_unit, valid_single_redirect_here)
{
	t_io_redirect *io_redirect;

	t_token	*token2 = init_token(WORD, "EOF", NULL);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DLESS, "<<", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	io_redirect = parse_io_redirect(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, io_redirect);
	cr_expect_eq(io_redirect->io_file, NULL);
	cr_expect_eq(io_redirect->io_number, NULL);
	cr_expect_eq(io_redirect->next, NULL);
	cr_assert_neq(io_redirect->io_here, NULL);
	cr_expect_str_eq(io_redirect->io_here->here_end, "EOF");
}

Test(parse_io_redirect_unit, valid_single_redirect_file)
{
	t_io_redirect *io_redirect;

	t_token	*token3 = init_token(WORD, "outfile", NULL);
	cr_assert_neq(NULL, token3, "malloc failed!");
	t_token	*token2 = init_token(DGREAT, ">>", token3);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(IO_NUMBER, "1", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	io_redirect = parse_io_redirect(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, io_redirect);
	cr_expect_eq(io_redirect->io_here, NULL);
	cr_expect_str_eq(io_redirect->io_number, "1");
	cr_expect_eq(io_redirect->next, NULL);
	cr_assert_neq(io_redirect->io_file, NULL);
	cr_expect_eq(io_redirect->io_file->redirect_op, redirect_append);
	cr_expect_str_eq(io_redirect->io_file->filename, "outfile");
}

Test(parse_io_redirect_unit, valid_two_redirects_here_file)
{
	t_io_redirect *io_redirect;

	t_token	*token4 = init_token(WORD, "42", NULL);
	cr_assert_neq(NULL, token4, "malloc failed!");
	t_token	*token3 = init_token(GREATAMP, ">&", token4);
	cr_assert_neq(NULL, token3, "malloc failed!");
	t_token	*token2 = init_token(WORD, "EOF", token3);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DLESS, "<<", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	io_redirect = parse_io_redirect(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, io_redirect);
	cr_expect_eq(io_redirect->io_file, NULL);
	cr_expect_eq(io_redirect->io_number, NULL);
	cr_assert_neq(io_redirect->io_here, NULL);
	cr_expect_str_eq(io_redirect->io_here->here_end, "EOF");
	cr_assert_neq(io_redirect->next, NULL);
	io_redirect = io_redirect->next;
	cr_expect_eq(io_redirect->io_here, NULL);
	cr_expect_eq(io_redirect->io_number, NULL);
	cr_expect_eq(io_redirect->next, NULL);
	cr_assert_neq(io_redirect->io_file, NULL);
	cr_expect_eq(io_redirect->io_file->redirect_op, redirect_fd_out);
	cr_expect_str_eq(io_redirect->io_file->filename, "42");
}

Test(parse_io_redirect_unit, invalid_null_token)
{
	t_io_redirect *io_redirect;
	t_token			*token = NULL;

	io_redirect = parse_io_redirect(&token);
	cr_assert_eq(NULL, io_redirect);
}

Test(parse_io_redirect_unit, invalid_null_token_pointer)
{
	t_io_redirect *io_redirect;

	io_redirect = parse_io_redirect(NULL);
	cr_assert_eq(NULL, io_redirect);
}

Test(free_io_redirect_unit, valid_free_two_redirects_here_file)
{
	t_io_redirect *io_redirect;

	t_token	*token4 = init_token(WORD, "42", NULL);
	cr_assert_neq(NULL, token4, "malloc failed!");
	t_token	*token3 = init_token(GREATAMP, ">&", token4);
	cr_assert_neq(NULL, token3, "malloc failed!");
	t_token	*token2 = init_token(WORD, "EOF", token3);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DLESS, "<<", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	io_redirect = parse_io_redirect(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, io_redirect);

	free_io_redirect(io_redirect);
}
