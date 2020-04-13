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

Test(parse_complete_command_unit, valid_single_redirect_here_nopipe)
{
	t_complete_cmd	*complete_command;
	t_simple_cmd	*simple_cmd;


	t_token	*token2 = init_token(WORD, "EOF", NULL);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DLESS, "<<", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	complete_command = parse_complete_command(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, complete_command);
	cr_expect_eq(complete_command->seperator_op, no_seperator_op);
	cr_assert_neq(NULL, complete_command->pipe_sequence);
	cr_expect_eq(complete_command->pipe_sequence->pipe, no_pipe);
	cr_assert_neq(NULL, complete_command->pipe_sequence->simple_command);
	simple_cmd = complete_command->pipe_sequence->simple_command;
	cr_expect_eq(simple_cmd->arguments, NULL);
	cr_expect_eq(simple_cmd->redirects->next, NULL);
	cr_assert_neq(simple_cmd->redirects, NULL);
	cr_expect_str_eq(simple_cmd->redirects->io_here->here_end, "EOF");
}

Test(parse_complete_command_unit, valid_redirect_arg_semi)
{
	t_complete_cmd *complete_command;
	t_simple_cmd *simple_cmd;

	t_token	*token4 = init_token(SEMI, ";", NULL);
	cr_assert_neq(NULL, token4, "malloc failed!");
	t_token	*token3 = init_token(WORD, "cat", token4);
	cr_assert_neq(NULL, token3, "malloc failed!");
	t_token	*token2 = init_token(WORD, "filename", token3);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DGREAT, ">>", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	complete_command = parse_complete_command(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, complete_command);
	cr_expect_eq(complete_command->seperator_op, semicolon_op);
	cr_assert_neq(NULL, complete_command->pipe_sequence);
	cr_expect_eq(complete_command->pipe_sequence->pipe, no_pipe);
	cr_assert_neq(complete_command->pipe_sequence->simple_command, NULL);
	simple_cmd = complete_command->pipe_sequence->simple_command;
	cr_expect_eq(simple_cmd->redirects->io_file->redirect_op, redirect_append);
	cr_expect_str_eq(simple_cmd->redirects->io_file->filename, "filename");
	cr_expect_eq(simple_cmd->redirects->next, NULL);
	cr_assert_neq(simple_cmd->arguments, NULL);
	cr_expect_str_eq(simple_cmd->arguments->argument, "cat");
	cr_expect_eq(simple_cmd->arguments->next, NULL);
}

Test(parse_complete_command_unit, valid_two_cmd_redirect_arg_semi)
{
	t_complete_cmd *complete_command;
	t_simple_cmd *simple_cmd;

	t_token	*token5 = init_token(WORD, "ps", NULL);
	cr_assert_neq(NULL, token5, "malloc failed!");
	t_token	*token4 = init_token(SEMI, ";", token5);
	cr_assert_neq(NULL, token4, "malloc failed!");
	t_token	*token3 = init_token(WORD, "cat", token4);
	cr_assert_neq(NULL, token3, "malloc failed!");
	t_token	*token2 = init_token(WORD, "filename", token3);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DGREAT, ">>", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	complete_command = parse_complete_command(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, complete_command);
	cr_expect_eq(complete_command->seperator_op, semicolon_op);
	cr_expect_neq(complete_command->next, NULL);
	cr_assert_neq(NULL, complete_command->pipe_sequence);
	cr_expect_eq(complete_command->pipe_sequence->pipe, no_pipe);
	cr_assert_neq(complete_command->pipe_sequence->simple_command, NULL);
	simple_cmd = complete_command->pipe_sequence->simple_command;
	cr_expect_eq(simple_cmd->redirects->io_file->redirect_op, redirect_append);
	cr_expect_str_eq(simple_cmd->redirects->io_file->filename, "filename");
	cr_expect_eq(simple_cmd->redirects->next, NULL);
	cr_assert_neq(simple_cmd->arguments, NULL);
	cr_expect_str_eq(simple_cmd->arguments->argument, "cat");
	cr_expect_eq(simple_cmd->arguments->next, NULL);
}

Test(free_complete_command_unit, valid_free_two_redirects_here_file)
{
	t_complete_cmd *complete_command;

	t_token	*token4 = init_token(WORD, "meson.build", NULL);
	cr_assert_neq(NULL, token4, "malloc failed!");
	t_token	*token3 = init_token(WORD, "cat", token4);
	cr_assert_neq(NULL, token3, "malloc failed!");
	t_token	*token2 = init_token(WORD, "filename", token3);
	cr_assert_neq(NULL, token2, "malloc failed!");
	t_token	*token1 = init_token(DGREAT, ">>", token2);
	cr_assert_neq(NULL, token1, "malloc failed!");
	t_token *tokens = token1;

	complete_command = parse_complete_command(&tokens);
	cr_expect_eq(tokens, NULL);
	cr_assert_neq(NULL, complete_command);

	free_complete_command(complete_command);
}
