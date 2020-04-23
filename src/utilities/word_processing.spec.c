/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_processing.spec.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 12:56:20 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/16 12:56:20 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "handle_input.h"

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

static int	diff_complete_command(t_complete_cmd *command1, t_complete_cmd *command2)
{
	t_argument		*argument1;
	t_argument		*argument2;
	t_pipe_sequence	*pipe_s1;
	t_pipe_sequence	*pipe_s2;
	t_io_redirect	*redir1;
	t_io_redirect	*redir2;

	while (command1 != NULL)
	{
		if (command2 == NULL)
			return (1);
		if (command1->seperator_op != command2->seperator_op)
			return (1);
		pipe_s1 = command1->pipe_sequence;
		pipe_s2 = command2->pipe_sequence;
		while (pipe_s1 != NULL)
		{
			if (pipe_s2 == NULL)
				return (1);
			if (pipe_s1->pipe != pipe_s2->pipe)
				return (1);
			if (pipe_s1->simple_command != NULL)
			{
				if (pipe_s2->simple_command == NULL)
					return (1);
				argument1 = pipe_s1->simple_command->arguments;
				argument2 = pipe_s2->simple_command->arguments;
				while (argument1 != NULL)
				{
					if (argument2 == NULL)
						return (1);
					if (argument1->argument != NULL)
					{
						if (argument2 == NULL)
							return (1);
						if (strcmp(argument1->argument, argument2->argument) != 0)
							return (1);
					}
					argument1 = pipe_s1->simple_command->arguments->next;
					argument2 = pipe_s2->simple_command->arguments->next;
				}
				if (argument2 != NULL)
					return (1);
				redir1 = pipe_s1->simple_command->redirects;
				redir2 = pipe_s2->simple_command->redirects;
				while (redir1 != NULL)
				{
					if (redir2 == NULL)
						return (1);
					if (strcmp(redir1->io_number, redir2->io_number) != 0)
						return (1);
					if (redir1->io_file != NULL)
					{
						if (redir2->io_file == NULL)
							return (1);
						if (redir1->io_file->filename != NULL)
						{
							if (redir2->io_file->filename == NULL)
								return (1);
							if (strcmp(redir1->io_file->filename, redir2->io_file->filename) != 0)
								return (1);
						}
						else if (redir1->io_file->filename != NULL)
							return (1);
						if (redir1->io_file->redirect_op != redir2->io_file->redirect_op)
							return (1);
					}
					else if (redir2->io_file != NULL)
						return (1);
					if (redir1->io_here != NULL)
					{
						if (redir2->io_here == NULL)
							return (1);
						if (redir1->io_here->here_end != NULL)
						{
							if (redir2->io_here->here_end == NULL)
								return (1);
							if (strcmp(redir1->io_here->here_end, redir2->io_here->here_end) != 0)
								return (1);
						}
						else if (redir2->io_here->here_end != NULL)
							return (1);
					}
					else if (redir2->io_here != NULL)
						return (1);
					redir1 = pipe_s1->simple_command->redirects->next;
					redir2 = pipe_s2->simple_command->redirects->next;
				}
				if (redir2 != NULL)
					return (1);
			}
			else if (pipe_s1->simple_command != NULL)
				return (1);
			pipe_s1 = command1->pipe_sequence->next;
			pipe_s2 = command2->pipe_sequence->next;
		}
		if (pipe_s2 != NULL)
			return (1);
		command1 = command1->next;
		command2 = command2->next;
	}
	if (command2 != NULL)
		return (1);
	return (0);
}

Test(word_processing_unit, valid_single_token_no_processing)
{
	t_token 		*token1 = init_token(WORD, "echo", NULL);
	t_token 		*token_start = token1;
	t_complete_cmd	*command;
	t_complete_cmd	*expected_command;
	int				ret;
	int				expected_ret = 0;
	int				expected_diff_ret = 0;

	token_start = token1;
	command = parse_complete_command(&token1);
	token1 = token_start;
	expected_command = parse_complete_command(&token1);
	ret = diff_complete_command(command, expected_command);
	cr_assert_eq(ret, expected_diff_ret, "FATAL in prep: expected return %i, got %i.", expected_diff_ret, ret);
	ret = word_processing(NULL, NULL, command);
	cr_expect_eq(ret, expected_ret, "expected return %i, got %i.", expected_ret, ret);
	ret = diff_complete_command(command, expected_command);
	cr_expect_eq(ret, expected_diff_ret, "expected return %i, got %i.", expected_diff_ret, ret);
}

Test(word_processing_unit, valid_single_token_remove_quotes)
{
	t_token 		*token1 = init_token(WORD, "\"echo\"", NULL);
	t_token 		*token_start = token1;
	t_complete_cmd	*command;
	t_complete_cmd	*expected_command;
	int				ret;
	int				expected_ret = 0;
	int				expected_diff_ret = 1;
	char			*expected_str = "echo";

	token_start = token1;
	command = parse_complete_command(&token1);
	token1 = token_start;
	expected_command = parse_complete_command(&token1);
	ret = diff_complete_command(command, expected_command);
	cr_assert_eq(ret, 0, "FATAL in prep: expected return %i, got %i.", 0, ret);
	ret = word_processing(NULL, NULL, command);
	cr_expect_eq(ret, expected_ret, "expected return %i, got %i.", expected_ret, ret);
	ret = diff_complete_command(command, expected_command);
	cr_expect_eq(ret, expected_diff_ret, "expected return %i, got %i.", expected_diff_ret, ret);
	cr_assert_neq(command, NULL);
	cr_assert_neq(expected_command, NULL);
	cr_expect_eq(NULL, command->next);
	cr_expect_eq(NULL, expected_command->next);
	cr_assert_neq(command->pipe_sequence, NULL);
	cr_assert_neq(expected_command->pipe_sequence, NULL);
	cr_expect_eq(NULL, command->pipe_sequence->next);
	cr_expect_eq(NULL, expected_command->pipe_sequence->next);
	cr_assert_neq(command->pipe_sequence->simple_command, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->arguments, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command->arguments, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->arguments->argument, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command->arguments->argument, NULL);
	cr_expect_str_eq(command->pipe_sequence->simple_command->arguments->argument, expected_str);
	cr_expect_eq(NULL, command->pipe_sequence->simple_command->arguments->next);
	cr_expect_eq(NULL, expected_command->pipe_sequence->simple_command->arguments->next);
}

Test(word_processing_unit, valid_argument_redir_remove_quotes)
{
	t_token 		*token3 = init_token(WORD, "hel\"l\"o", NULL);
	t_token 		*token2 = init_token(DGREAT, ">>", token3);
	t_token 		*token1 = init_token(WORD, "\"echo\"", token2);
	t_token 		*token_start = token1;
	t_complete_cmd	*command;
	t_complete_cmd	*expected_command;
	int				ret;
	int				expected_ret = 0;
	int				expected_diff_ret = 1;
	char			*expected_str = "echo";

	token_start = token1;
	command = parse_complete_command(&token1);
	token1 = token_start;
	expected_command = parse_complete_command(&token1);
	ret = word_processing(NULL, NULL, command);
	cr_expect_eq(ret, expected_ret, "expected return %i, got %i.", expected_ret, ret);
	ret = diff_complete_command(command, expected_command);
	cr_expect_eq(ret, expected_diff_ret, "expected return %i, got %i.", expected_diff_ret, ret);
	cr_assert_neq(command, NULL);
	cr_assert_neq(expected_command, NULL);
	cr_expect_eq(NULL, command->next);
	cr_expect_eq(NULL, expected_command->next);
	cr_assert_neq(command->pipe_sequence, NULL);
	cr_assert_neq(expected_command->pipe_sequence, NULL);
	cr_expect_eq(NULL, command->pipe_sequence->next);
	cr_expect_eq(NULL, expected_command->pipe_sequence->next);
	cr_assert_neq(command->pipe_sequence->simple_command, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->arguments, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command->arguments, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->arguments->argument, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command->arguments->argument, NULL);
	cr_expect_str_eq(command->pipe_sequence->simple_command->arguments->argument, expected_str);
	cr_expect_eq(NULL, command->pipe_sequence->simple_command->arguments->next);
	cr_expect_eq(NULL, expected_command->pipe_sequence->simple_command->arguments->next);
	expected_str = "hello";
	cr_assert_neq(command->pipe_sequence->simple_command->redirects, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command->redirects, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->redirects->io_file, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command->redirects->io_file, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->redirects->io_file->filename, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command->redirects->io_file->filename, NULL);
	cr_expect_str_eq(command->pipe_sequence->simple_command->redirects->io_file->filename, expected_str);
	cr_expect_eq(command->pipe_sequence->simple_command->redirects->io_here, NULL);
	cr_expect_eq(expected_command->pipe_sequence->simple_command->redirects->io_here, NULL);
}

Test(word_processing_unit, valid_two_arguments_redir_remove_quotes)
{
	t_token 		*token4 = init_token(WORD, "\"bye\"", NULL);
	t_token 		*token3 = init_token(WORD, "hel\"l\"o", token4);
	t_token 		*token2 = init_token(DGREAT, ">>", token3);
	t_token 		*token1 = init_token(WORD, "\"echo\"", token2);
	t_token 		*token_start = token1;
	t_complete_cmd	*command;
	t_complete_cmd	*expected_command;
	int				ret;
	int				expected_ret = 0;
	int				expected_diff_ret = 1;
	char			*expected_str = "echo";

	token_start = token1;
	command = parse_complete_command(&token1);
	token1 = token_start;
	expected_command = parse_complete_command(&token1);
	ret = word_processing(NULL, NULL, command);
	cr_expect_eq(ret, expected_ret, "expected return %i, got %i.", expected_ret, ret);
	ret = diff_complete_command(command, expected_command);
	cr_expect_eq(ret, expected_diff_ret, "expected return %i, got %i.", expected_diff_ret, ret);
	cr_assert_neq(command, NULL);
	cr_assert_neq(expected_command, NULL);
	cr_expect_eq(NULL, command->next);
	cr_expect_eq(NULL, expected_command->next);
	cr_assert_neq(command->pipe_sequence, NULL);
	cr_assert_neq(expected_command->pipe_sequence, NULL);
	cr_expect_eq(NULL, command->pipe_sequence->next);
	cr_expect_eq(NULL, expected_command->pipe_sequence->next);
	cr_assert_neq(command->pipe_sequence->simple_command, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->arguments, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command->arguments, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->arguments->argument, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command->arguments->argument, NULL);
	cr_expect_str_eq(command->pipe_sequence->simple_command->arguments->argument, expected_str);
	cr_expect_neq(NULL, command->pipe_sequence->simple_command->arguments->next);
	cr_expect_neq(NULL, expected_command->pipe_sequence->simple_command->arguments->next);
	command->pipe_sequence->simple_command->arguments = command->pipe_sequence->simple_command->arguments->next;
	expected_str = "bye";
	cr_assert_neq(command->pipe_sequence->simple_command->arguments->argument, NULL);
	cr_expect_str_eq(command->pipe_sequence->simple_command->arguments->argument, expected_str);
	expected_str = "hello";
	cr_assert_neq(command->pipe_sequence->simple_command->redirects, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command->redirects, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->redirects->io_file, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command->redirects->io_file, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->redirects->io_file->filename, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command->redirects->io_file->filename, NULL);
	cr_expect_str_eq(command->pipe_sequence->simple_command->redirects->io_file->filename, expected_str);
	cr_expect_eq(command->pipe_sequence->simple_command->redirects->io_here, NULL);
	cr_expect_eq(expected_command->pipe_sequence->simple_command->redirects->io_here, NULL);
}

Test(word_processing_unit, valid_argument_redir_expansion_with_quotes)
{
	t_token 		*token3 = init_token(WORD, "$foo", NULL);
	t_token 		*token2 = init_token(DGREAT, ">>", token3);
	t_token 		*token1 = init_token(WORD, "\"$foo\"", token2);
	t_token 		*token_start = token1;
	t_complete_cmd	*command;
	t_complete_cmd	*expected_command;
	t_env			*env_list = ft_memalloc(sizeof(t_env) * 1);
	int				ret;
	int				expected_ret = 0;
	int				expected_diff_ret = 1;
	char			*expected_str = "bar";

	env_list->key = "foo";
	env_list->value = "bar";
	env_list->next = NULL;
	token_start = token1;
	command = parse_complete_command(&token1);
	token1 = token_start;
	expected_command = parse_complete_command(&token1);
	ret = word_processing(NULL, env_list, command);
	cr_expect_eq(ret, expected_ret, "expected return %i, got %i.", expected_ret, ret);
	ret = diff_complete_command(command, expected_command);
	cr_expect_eq(ret, expected_diff_ret, "expected return %i, got %i.", expected_diff_ret, ret);
	cr_assert_neq(command, NULL);
	cr_assert_neq(expected_command, NULL);
	cr_expect_eq(NULL, command->next);
	cr_expect_eq(NULL, expected_command->next);
	cr_assert_neq(command->pipe_sequence, NULL);
	cr_assert_neq(expected_command->pipe_sequence, NULL);
	cr_expect_eq(NULL, command->pipe_sequence->next);
	cr_expect_eq(NULL, expected_command->pipe_sequence->next);
	cr_assert_neq(command->pipe_sequence->simple_command, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->arguments, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command->arguments, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->arguments->argument, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command->arguments->argument, NULL);
	cr_expect_str_eq(command->pipe_sequence->simple_command->arguments->argument, expected_str);
	cr_expect_eq(NULL, command->pipe_sequence->simple_command->arguments->next);
	cr_expect_eq(NULL, expected_command->pipe_sequence->simple_command->arguments->next);
	cr_assert_neq(command->pipe_sequence->simple_command->redirects, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command->redirects, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->redirects->io_file, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command->redirects->io_file, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->redirects->io_file->filename, NULL);
	cr_assert_neq(expected_command->pipe_sequence->simple_command->redirects->io_file->filename, NULL);
	cr_expect_str_eq(command->pipe_sequence->simple_command->redirects->io_file->filename, expected_str);
	cr_expect_eq(command->pipe_sequence->simple_command->redirects->io_here, NULL);
	cr_expect_eq(expected_command->pipe_sequence->simple_command->redirects->io_here, NULL);
}

Test(word_processing_unit, valid_redir_here_doc)
{
	t_token 		*token2 = init_token(WORD, "\"$foo\"", NULL);
	t_token 		*token1 = init_token(DLESS, "<<", token2);
	t_complete_cmd	*command;
	int				ret;
	int				expected_ret = 0;
	char			*expected_str = "$foo";

	command = parse_complete_command(&token1);
	ret = word_processing(NULL, NULL, command);
	cr_expect_eq(ret, expected_ret, "expected return %i, got %i.", expected_ret, ret);
	cr_assert_neq(command, NULL);
	cr_expect_eq(NULL, command->next);
	cr_assert_neq(command->pipe_sequence, NULL);
	cr_expect_eq(NULL, command->pipe_sequence->next);
	cr_assert_neq(command->pipe_sequence->simple_command, NULL);
	cr_expect_eq(command->pipe_sequence->simple_command->arguments, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->redirects, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->redirects->io_here, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->redirects->io_here->here_end, NULL);
	cr_expect_str_eq(command->pipe_sequence->simple_command->redirects->io_here->here_end, expected_str);
	cr_expect_eq(command->pipe_sequence->simple_command->redirects->io_file, NULL);
}

Test(word_processing_unit, invalid_NULL_shell_unterminated_quote)
{
	t_token 		*token3 = init_token(WORD, "$foo", NULL);
	t_token 		*token2 = init_token(DGREAT, ">>", token3);
	t_token 		*token1 = init_token(WORD, "\"$foo", token2);
	t_token 		*token_start = token1;
	t_complete_cmd	*command;
	t_env			*env_list = ft_memalloc(sizeof(t_env) * 1);
	int				ret;
	int				expected_ret = -1;
	char			*expected_str = "bar";
	char			*expected_str2 = "\"$foo";

	env_list->key = "foo";
	env_list->value = "bar";
	env_list->next = NULL;
	token_start = token1;
	command = parse_complete_command(&token1);
	token1 = token_start;
	ret = word_processing(NULL, env_list, command);
	cr_expect_eq(ret, expected_ret, "expected return %i, got %i.", expected_ret, ret);
	cr_assert_neq(command, NULL);
	cr_expect_eq(NULL, command->next);
	cr_assert_neq(command->pipe_sequence, NULL);
	cr_expect_eq(NULL, command->pipe_sequence->next);
	cr_assert_neq(command->pipe_sequence->simple_command, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->arguments, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->arguments->argument, NULL);
	cr_expect_str_eq(command->pipe_sequence->simple_command->arguments->argument, expected_str2);
	cr_expect_eq(NULL, command->pipe_sequence->simple_command->arguments->next);
	cr_assert_neq(command->pipe_sequence->simple_command->redirects, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->redirects->io_file, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->redirects->io_file->filename, NULL);
	cr_expect_str_eq(command->pipe_sequence->simple_command->redirects->io_file->filename, expected_str);
	cr_expect_eq(command->pipe_sequence->simple_command->redirects->io_here, NULL);
}

Test(word_processing_unit, valid_NULL_env_expansions)
{
	t_token 		*token3 = init_token(WORD, "$foo", NULL);
	t_token 		*token2 = init_token(DGREAT, ">>", token3);
	t_token 		*token1 = init_token(WORD, "\"$foo\"", token2);
	t_token 		*token_start = token1;
	t_complete_cmd	*command;
	int				ret;
	int				expected_ret = 0;
	char			*expected_str = "";

	token_start = token1;
	command = parse_complete_command(&token1);
	token1 = token_start;
	ret = word_processing(NULL, NULL, command);
	cr_expect_eq(ret, expected_ret, "expected return %i, got %i.", expected_ret, ret);
	cr_assert_neq(command, NULL);
	cr_expect_eq(NULL, command->next);
	cr_assert_neq(command->pipe_sequence, NULL);
	cr_expect_eq(NULL, command->pipe_sequence->next);
	cr_assert_neq(command->pipe_sequence->simple_command, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->arguments, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->arguments->argument, NULL);
	cr_expect_str_eq(command->pipe_sequence->simple_command->arguments->argument, expected_str);
	cr_expect_eq(NULL, command->pipe_sequence->simple_command->arguments->next);
	cr_assert_neq(command->pipe_sequence->simple_command->redirects, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->redirects->io_file, NULL);
	cr_assert_neq(command->pipe_sequence->simple_command->redirects->io_file->filename, NULL);
	cr_expect_str_eq(command->pipe_sequence->simple_command->redirects->io_file->filename, expected_str);
	cr_expect_eq(command->pipe_sequence->simple_command->redirects->io_here, NULL);
}

Test(word_processing_unit, invalid_NULL_command)
{
	t_env			*env_list = ft_memalloc(sizeof(t_env) * 1);
	int				ret;
	int				expected_ret = -1;

	env_list->key = "foo";
	env_list->value = "bar";
	env_list->next = NULL;
	ret = word_processing(NULL, env_list, NULL);
	cr_expect_eq(ret, expected_ret, "expected return %i, got %i.", expected_ret, ret);
}
