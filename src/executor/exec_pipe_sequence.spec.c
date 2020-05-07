/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_pipe_sequence.spec.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 15:46:44 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/28 15:46:44 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "executor.h"
#include "error_str.h"

static void redirect_std_out()
{
	cr_redirect_stdout();
}

static void redirect_std_err_out()
{
	cr_redirect_stderr();
	cr_redirect_stdout();
}

Test(exec_pipe_sequence_unit, valid_basic_command, .init = redirect_std_out)
{
	char			**argv = ft_strsplit("/bin/echo foo", ' ');
	t_argument		argument2 = {strdup("foo"), NULL};
	t_argument		argument1 = {strdup("/bin/echo"), &argument2};
	t_simple_cmd	simple_cmd = {NULL, &argument1, argv};
	t_pipe_sequence	pipe_seq = {&simple_cmd, no_pipe, NULL};
	int				ret;
	int				exp_ret = 0;

	ret = exec_pipe_sequence(&pipe_seq, dup_sys_env());
	cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
	fflush(stdout);
	cr_expect_stdout_eq_str("foo\n");
}

Test(exec_pipe_sequence_unit, valid_pipe_sequence_2_commands, .init = redirect_std_out)
{
	char			**argv1 = ft_strsplit("/bin/echo foo", ' ');
	char			**argv2 = ft_strsplit("cat -e", ' ');
	t_argument		argument_cat2 = {strdup("-e"), NULL};
	t_argument		argument_cat1 = {strdup("cat"), &argument_cat2};
	t_argument		argument2 = {strdup("foo"), NULL};
	t_argument		argument1 = {strdup("/bin/echo"), &argument2};
	t_simple_cmd	simple_cmd1 = {NULL, &argument1, argv1};
	t_simple_cmd	simple_cmd2 = {NULL, &argument_cat1, argv2};
	t_pipe_sequence	pipe_seq2 = {&simple_cmd2, no_pipe, NULL};
	t_pipe_sequence	pipe_seq1 = {&simple_cmd1, pipe_op, &pipe_seq2};
	int				ret;
	int				exp_ret = 0;

	ret = exec_pipe_sequence(&pipe_seq1, dup_sys_env());
	cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
	fflush(stdout);
	cr_expect_stdout_eq_str("foo$\n");
}

Test(exec_pipe_sequence_unit, invalid_pipe_sequence_2_commands_no_pipe_op, .init = redirect_std_err_out)
{
	char			**argv1 = ft_strsplit("/bin/echo foo", ' ');
	char			**argv2 = ft_strsplit("cat -e", ' ');
	t_argument		argument_cat2 = {strdup("-e"), NULL};
	t_argument		argument_cat1 = {strdup("cat"), &argument_cat2};
	t_argument		argument2 = {strdup("foo"), NULL};
	t_argument		argument1 = {strdup("/bin/echo"), &argument2};
	t_simple_cmd	simple_cmd1 = {NULL, &argument1, argv1};
	t_simple_cmd	simple_cmd2 = {NULL, &argument_cat1, argv2};
	t_pipe_sequence	pipe_seq2 = {&simple_cmd2, no_pipe, NULL};
	t_pipe_sequence	pipe_seq1 = {&simple_cmd1, no_pipe, &pipe_seq2};
	int				ret;
	int				exp_ret = parsing_error;
	char			buff[1024];

	ret = exec_pipe_sequence(&pipe_seq1, dup_sys_env());
	cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
	fflush(stdout);
	cr_expect_stdout_eq_str("foo\n");
	fflush(stderr);
	sprintf(buff, "%.978s: no pipe operator, but more pipe sequences\n", g_error_str[parsing_error]);
	cr_expect_stderr_eq_str(buff);
}

Test(exec_pipe_sequence_unit, invalid_NULL_env)
{
	char			**argv = ft_strsplit("/bin/echo foo", ' ');
	t_argument		argument2 = {strdup("foo"), NULL};
	t_argument		argument1 = {strdup("/bin/echo"), &argument2};
	t_simple_cmd	simple_cmd = {NULL, &argument1, argv};
	t_pipe_sequence	pipe_seq = {&simple_cmd, no_pipe, NULL};
	int				ret;
	int				exp_ret = parsing_error;

	ret = exec_pipe_sequence(&pipe_seq, NULL);
	cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
}

Test(exec_pipe_sequence_unit, invalid_empty_simple_cmd)
{
	t_simple_cmd	simple_cmd = {NULL, NULL, NULL};
	t_pipe_sequence	pipe_seq = {&simple_cmd, no_pipe, NULL};
	int				ret;
	int				exp_ret = parsing_error;

	ret = exec_pipe_sequence(&pipe_seq, dup_sys_env());
	cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
}

Test(exec_pipe_sequence_unit, invalid_NULL_simple_cmd_pipe)
{
	t_pipe_sequence	pipe_seq = {NULL, pipe_op, NULL};
	int				ret;
	int				exp_ret = parsing_error;

	ret = exec_pipe_sequence(&pipe_seq, dup_sys_env());
	cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
}

Test(exec_pipe_sequence_unit, invalid_NULL_pipe_seq)
{
	int				ret;
	int				exp_ret = parsing_error;

	ret = exec_pipe_sequence(NULL, dup_sys_env());
	cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
}
