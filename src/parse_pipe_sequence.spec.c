/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_pipe_sequence.spec.c                           :+:    :+:            */
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

Test(parse_pipe_sequence_unit, valid_single_redirect_here_nopipe)
{
	t_pipe_sequence *pipe_sequence;
	t_simple_cmd *simple_cmd;


	t_token	*token2 = init_token(WORD, "EOF", NULL);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DLESS, "<<", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	pipe_sequence = parse_pipe_sequence(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, pipe_sequence);
	cr_expect_eq(pipe_sequence->pipe, no_pipe);
	cr_assert_neq(NULL, pipe_sequence->simple_command);
	simple_cmd = pipe_sequence->simple_command;
	cr_expect_eq(simple_cmd->arguments, NULL);
	cr_expect_eq(simple_cmd->redirects->next, NULL);
	cr_assert_neq(simple_cmd->redirects, NULL);
	cr_expect_str_eq(simple_cmd->redirects->io_here->here_end, "EOF");
}

Test(parse_pipe_sequence_unit, valid_redirect_arg_pipe)
{
	t_pipe_sequence *pipe_sequence;
	t_simple_cmd *simple_cmd;

	t_token	*token4 = init_token(PIPE, "|", NULL);
	cr_assert_neq(NULL, token4, "malloc failed!");
	t_token	*token3 = init_token(WORD, "cat", token4);
	cr_assert_neq(NULL, token3, "malloc failed!");
	t_token	*token2 = init_token(WORD, "filename", token3);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DGREAT, ">>", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	pipe_sequence = parse_pipe_sequence(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, pipe_sequence);
	cr_assert_neq(pipe_sequence->simple_command, NULL);
	simple_cmd = pipe_sequence->simple_command;
	cr_expect_eq(simple_cmd->redirects->io_file->redirect_op, redirect_append);
	cr_expect_str_eq(simple_cmd->redirects->io_file->filename, "filename");
	cr_expect_eq(simple_cmd->redirects->next, NULL);
	cr_assert_neq(simple_cmd->arguments, NULL);
	cr_expect_str_eq(simple_cmd->arguments->argument, "cat");
	cr_expect_eq(simple_cmd->arguments->next, NULL);
	cr_expect_eq(pipe_sequence->pipe, pipe_op);
}

Test(parse_pipe_sequence_unit, valid_redirect_arg_pipe_cmd)
{
	t_pipe_sequence *pipe_sequence;
	t_simple_cmd *simple_cmd;

	t_token	*token5 = init_token(WORD, "cat", NULL);
	cr_assert_neq(NULL, token5, "malloc failed!");
	t_token	*token4 = init_token(PIPE, "|", token5);
	cr_assert_neq(NULL, token4, "malloc failed!");
	t_token	*token3 = init_token(WORD, "ps", token4);
	cr_assert_neq(NULL, token3, "malloc failed!");
	t_token	*token2 = init_token(WORD, "filename", token3);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DGREAT, ">>", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	pipe_sequence = parse_pipe_sequence(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, pipe_sequence);
	cr_expect_neq(pipe_sequence->next, NULL);
	cr_assert_neq(pipe_sequence->simple_command, NULL);
	simple_cmd = pipe_sequence->simple_command;
	cr_expect_eq(simple_cmd->redirects->io_file->redirect_op, redirect_append);
	cr_expect_str_eq(simple_cmd->redirects->io_file->filename, "filename");
	cr_expect_eq(simple_cmd->redirects->next, NULL);
	cr_assert_neq(simple_cmd->arguments, NULL);
	cr_expect_str_eq(simple_cmd->arguments->argument, "ps");
	cr_expect_eq(simple_cmd->arguments->next, NULL);
	cr_expect_eq(pipe_sequence->pipe, pipe_op);
}

Test(free_pipe_sequence_unit, valid_free_two_redirects_here_file)
{
	t_pipe_sequence *pipe_sequence;

	t_token	*token4 = init_token(WORD, "meson.build", NULL);
	cr_assert_neq(NULL, token4, "malloc failed!");
	t_token	*token3 = init_token(WORD, "cat", token4);
	cr_assert_neq(NULL, token3, "malloc failed!");
	t_token	*token2 = init_token(WORD, "filename", token3);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DGREAT, ">>", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	pipe_sequence = parse_pipe_sequence(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, pipe_sequence);

	free_pipe_sequence(pipe_sequence);
}
