/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_complete_command.spec.c                       :+:    :+:            */
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

static void redirect_std_err()
{
	cr_redirect_stderr();
}

static void redirect_std_err_out()
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

Test(exec_complete_command_unit, valid_basic_command, .init = redirect_std_err_out)
{
	char			**argv = ft_strsplit("/bin/echo foo", ' ');
	t_argument		argument2 = {strdup("foo"), NULL};
	t_argument		argument1 = {strdup("/bin/echo"), &argument2};
	t_simple_cmd	simple_cmd = {NULL, &argument1, argv};
	t_pipe_sequence	pipe_seq = {&simple_cmd, "/bin/echo foo ;", no_pipe, NULL};
	t_complete_cmd	command = {&pipe_seq, "/bin/echo foo ;", semicolon_op, NULL};
	int				ret;
	int				exp_ret = 3;

	ret = exec_complete_command(NULL, &command);
	cr_expect_eq(ret, exp_ret, "expected ret %i but got %i!", exp_ret, ret);
	printf("-");
	dprintf(2, "-");
	fflush(stdout);
	cr_expect_stdout_eq_str("-");
	fflush(stderr);
	cr_expect_stderr_eq_str("-");
}

Test(exec_complete_command_unit, invalid_empty_simple_cmd, .init = redirect_std_err)
{
	t_simple_cmd	simple_cmd = {NULL, NULL, NULL};
	t_pipe_sequence	pipe_seq = {&simple_cmd, "", no_pipe, NULL};
	t_complete_cmd	command = {&pipe_seq, "", semicolon_op, NULL};
	int				ret;
	int				exp_ret = parsing_error;
	char			buff[1024];

	ret = exec_complete_command(NULL, &command);
	cr_expect_eq(ret, exp_ret, "expected ret %i but got %i!", exp_ret, ret);
	fflush(stderr);
	snprintf(buff, 1024, "Cetushell: %s: no arguments\n", g_error_str[parsing_error]);
	cr_expect_stderr_eq_str(buff);
}

Test(exec_complete_command_unit, invalid_NULL_simple_cmd_no_pipe, .init = redirect_std_err)
{
	t_pipe_sequence	pipe_seq = {NULL, "", no_pipe, NULL};
	t_complete_cmd	command = {&pipe_seq, "", semicolon_op, NULL};
	int				ret;
	int				exp_ret = parsing_error;
	char			buff[1024];

	ret = exec_complete_command(NULL, &command);
	cr_expect_eq(ret, exp_ret, "expected ret %i but got %i!", exp_ret, ret);
	fflush(stdout);
	snprintf(buff, 1024, "Cetushell: %s: NULL simple command\n", g_error_str[parsing_error]);
	cr_expect_stderr_eq_str(buff);
}

Test(exec_complete_command_unit, invalid_NULL_pipe_seq, .init = redirect_std_err)
{
	t_complete_cmd	command = {NULL, "", semicolon_op, NULL};
	int				ret;
	int				exp_ret = parsing_error;
	char			buff[1024];

	ret = exec_complete_command(NULL, &command);
	cr_expect_eq(ret, exp_ret, "expected ret %i but got %i!", exp_ret, ret);
	fflush(stdout);
	snprintf(buff, 1024, "Cetushell: %s: NULL pipe sequence\n", g_error_str[parsing_error]);
	cr_expect_stderr_eq_str(buff);
}

//should return 0 as no commands is weird, but not necessarily an error state.
Test(exec_complete_command_unit, invalid_NULL_complete_command)
{
	int				ret;
	int				exp_ret = 0;

	ret = exec_complete_command(NULL, NULL);
	cr_expect_eq(ret, exp_ret, "expected ret %i but got %i!", exp_ret, ret);
}
