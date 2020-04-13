/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_simple_command.spec.c                           :+:    :+:            */
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

Test(parse_simple_command_unit, valid_single_redirect_here)
{
	t_simple_cmd *simple_command;

	t_token	*token2 = init_token(WORD, "EOF", NULL);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DLESS, "<<", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	simple_command = parse_simple_command(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, simple_command);
	cr_expect_eq(simple_command->arguments, NULL);
	cr_expect_eq(simple_command->redirects->next, NULL);
	cr_assert_neq(simple_command->redirects, NULL);
	cr_expect_str_eq(simple_command->redirects->io_here->here_end, "EOF");
}

Test(parse_simple_command_unit, valid_redirect_and_two_arg)
{
	t_simple_cmd *simple_command;

	t_token	*token4 = init_token(WORD, "meson.build", NULL);
	cr_assert_neq(NULL, token4, "malloc failed!");
	t_token	*token3 = init_token(WORD, "cat", token4);
	cr_assert_neq(NULL, token3, "malloc failed!");
	t_token	*token2 = init_token(WORD, "filename", token3);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DGREAT, ">>", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	simple_command = parse_simple_command(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, simple_command);
	cr_assert_neq(simple_command->redirects, NULL);
	cr_expect_eq(simple_command->redirects->io_file->redirect_op, redirect_append);
	cr_expect_str_eq(simple_command->redirects->io_file->filename, "filename");
	cr_expect_eq(simple_command->redirects->next, NULL);
	cr_assert_neq(simple_command->arguments, NULL);
	cr_expect_str_eq(simple_command->arguments->argument, "cat");
	cr_assert_neq(simple_command->arguments->next, NULL);
	simple_command->arguments = simple_command->arguments->next;
	cr_expect_eq(simple_command->arguments->next, NULL);
	cr_expect_str_eq(simple_command->arguments->argument, "meson.build");
}

Test(parse_simple_command_unit, valid_redirect_and_two_arg_different_order)
{
	t_simple_cmd *simple_command;

	t_token	*token4 = init_token(WORD, "meson.build", NULL);
	cr_assert_neq(NULL, token4, "malloc failed!");
	t_token	*token3 = init_token(WORD, "filename", token4);
	cr_assert_neq(NULL, token3, "malloc failed!");
	t_token	*token2 = init_token(DGREAT, ">>", token3);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(WORD, "cat", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	simple_command = parse_simple_command(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, simple_command);
	cr_assert_neq(simple_command->redirects, NULL);
	cr_expect_eq(simple_command->redirects->io_file->redirect_op, redirect_append);
	cr_expect_str_eq(simple_command->redirects->io_file->filename, "filename");
	cr_expect_eq(simple_command->redirects->next, NULL);
	cr_assert_neq(simple_command->arguments, NULL);
	cr_expect_str_eq(simple_command->arguments->argument, "cat");
	cr_assert_neq(simple_command->arguments->next, NULL);
	simple_command->arguments = simple_command->arguments->next;
	cr_expect_eq(simple_command->arguments->next, NULL);
	cr_expect_str_eq(simple_command->arguments->argument, "meson.build");
}

Test(parse_simple_command_unit, valid_two_redirects_and_arg_different_order)
{
	t_simple_cmd *simple_command;
	t_token	*token5 = init_token(WORD, "EOF", NULL);
	cr_assert_neq(NULL, token5, "malloc failed!");
	t_token	*token4 = init_token(DLESS, "<<", token5);
	cr_assert_neq(NULL, token4, "malloc failed!");
	t_token	*token3 = init_token(WORD, "cat", token4);
	cr_assert_neq(NULL, token3, "malloc failed!");
	t_token	*token2 = init_token(WORD, "filename", token3);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DGREAT, ">>", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	simple_command = parse_simple_command(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, simple_command);
	cr_assert_neq(simple_command->redirects, NULL);
	cr_expect_eq(simple_command->redirects->io_file->redirect_op, redirect_append);
	cr_expect_str_eq(simple_command->redirects->io_file->filename, "filename");
	cr_assert_neq(simple_command->redirects->next, NULL);
	simple_command->redirects = simple_command->redirects->next;
	cr_expect_str_eq(simple_command->redirects->io_here->here_end, "EOF");
	cr_assert_neq(simple_command->arguments, NULL);
	cr_expect_str_eq(simple_command->arguments->argument, "cat");
	cr_expect_eq(simple_command->arguments->next, NULL);
}

Test(free_simple_command_unit, valid_free_two_redirects_here_file)
{
	t_simple_cmd *simple_command;

	t_token	*token4 = init_token(WORD, "meson.build", NULL);
	cr_assert_neq(NULL, token4, "malloc failed!");
	t_token	*token3 = init_token(WORD, "cat", token4);
	cr_assert_neq(NULL, token3, "malloc failed!");
	t_token	*token2 = init_token(WORD, "filename", token3);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DGREAT, ">>", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	simple_command = parse_simple_command(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, simple_command);

	free_simple_command(simple_command);
}
