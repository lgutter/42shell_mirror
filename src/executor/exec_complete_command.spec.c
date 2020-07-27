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
	cr_redirect_stderr();
	cr_redirect_stdout();
}

static int	redirect_std_out(char *filename)
{
	int fd = open(filename, O_TRUNC | O_WRONLY | O_CREAT, 0664);
	if (fd > 0)
	{
		if (dup2(fd, STDOUT_FILENO) != STDOUT_FILENO)
		{
			close(fd);
			return (-1);
		}
	}
	return (fd);
}

Test(exec_complete_command_unit, valid_basic_command, .init = redirect_std_err_out)
{
	char			**argv = ft_strsplit("/bin/echo foo", ' ');
	t_argument		argument2 = {strdup("foo"), NULL};
	t_argument		argument1 = {strdup("/bin/echo"), &argument2};
	t_simple_cmd	simple_cmd = {NULL, &argument1, argv};
	t_pipe_sequence	pipe_seq = {&simple_cmd, "/bin/echo foo ;", no_pipe, NULL};
	t_complete_cmd	command = {&pipe_seq, "/bin/echo foo ;", semicolon_op, NULL};
	t_shell			shell;
	t_job_cont		job_control;
	t_env			env = {strdup(""), strdup(""), 0, NULL};
	int				ret;
	int				exp_ret = 0;

	memset(&shell, 0, sizeof(t_shell));
	memset(&job_control, 0, sizeof(t_job_cont));
	shell.job_control = &job_control;
	shell.interactive = true;
	shell.env = &env;
	ret = exec_complete_command(&shell, &command);
	cr_expect_eq(ret, exp_ret, "expected ret %i but got %i!", exp_ret, ret);
	cr_expect_str_eq(shell.env->key, "?");
	cr_expect_str_eq(shell.env->value, "0");
	dprintf(2, "-");
	fflush(stdout);
	cr_expect_stdout_eq_str("foo\n");
	fflush(stderr);
	cr_expect_stderr_eq_str("-");
	cr_expect_eq(shell.job_control->current, 0);
	cr_expect_eq(shell.job_control->previous, 0);
	cr_expect_null(shell.job_control->job_list);
}

Test(exec_complete_command_unit, valid_basic_piped_command, .init = redirect_std_err_out)
{
	char			**argv2 = ft_strsplit("/bin/cat", ' ');
	char			**argv = ft_strsplit("/bin/echo foo", ' ');
	t_argument		argument21 = {strdup("/bin/cat"), NULL};
	t_argument		argument12 = {strdup("foo"), NULL};
	t_argument		argument11 = {strdup("/bin/echo"), &argument12};
	t_simple_cmd	simple_cmd2 = {NULL, &argument21, argv2};
	t_simple_cmd	simple_cmd = {NULL, &argument11, argv};
	t_pipe_sequence	pipe_seq2 = {&simple_cmd2, "/bin/cat", no_pipe, NULL};
	t_pipe_sequence	pipe_seq = {&simple_cmd, "/bin/echo foo |", pipe_op, &pipe_seq2};
	t_complete_cmd	command = {&pipe_seq, "/bin/echo foo | cat", semicolon_op, NULL};
	t_shell			shell;
	t_job_cont		job_control;
	t_env			env = {strdup(""), strdup(""), 0, NULL};
	int				ret;
	int				exp_ret = 0;

	memset(&shell, 0, sizeof(t_shell));
	memset(&job_control, 0, sizeof(t_job_cont));
	shell.job_control = &job_control;
	shell.interactive = true;
	shell.env = &env;
	ret = exec_complete_command(&shell, &command);
	cr_expect_eq(ret, exp_ret, "expected ret %i but got %i!", exp_ret, ret);
	cr_expect_str_eq(shell.env->key, "?");
	cr_expect_str_eq(shell.env->value, "0");
	dprintf(2, "-");
	fflush(stdout);
	cr_expect_stdout_eq_str("foo\n");
	fflush(stderr);
	cr_expect_stderr_eq_str("-");
	cr_expect_eq(shell.job_control->current, 0);
	cr_expect_eq(shell.job_control->previous, 0);
	cr_expect_null(shell.job_control->job_list);
}

Test(exec_complete_command_unit, valid_basic_piped_command_terminate_first, .init = redirect_std_err)
{
	char			**argv3 = ft_strsplit("wc -c", ' ');
	char			**argv2 = ft_strsplit("head -c 1000", ' ');
	char			**argv = ft_strsplit("base64 /dev/urandom", ' ');
	t_argument		argument32 = {strdup("-c"), NULL};
	t_argument		argument31 = {strdup("wc"), &argument32};
	t_argument		argument23 = {strdup("1000"), NULL};
	t_argument		argument22 = {strdup("-c"), &argument23};
	t_argument		argument21 = {strdup("head"), &argument22};
	t_argument		argument12 = {strdup("/dev/urandom"), NULL};
	t_argument		argument11 = {strdup("base64"), &argument12};
	t_simple_cmd	simple_cmd3 = {NULL, &argument31, argv3};
	t_simple_cmd	simple_cmd2 = {NULL, &argument21, argv2};
	t_simple_cmd	simple_cmd = {NULL, &argument11, argv};
	t_pipe_sequence	pipe_seq3 = {&simple_cmd3, "wc -c", no_pipe, NULL};
	t_pipe_sequence	pipe_seq2 = {&simple_cmd2, "head -c 1000 |", pipe_op, &pipe_seq3};
	t_pipe_sequence	pipe_seq = {&simple_cmd, "base64 /dev/urandom |", pipe_op, &pipe_seq2};
	t_complete_cmd	command = {&pipe_seq, "base64 /dev/urandom | head -c 1000 | wc -c", semicolon_op, NULL};
	t_shell			shell;
	t_job_cont		job_control;
	t_env			env2 = {strdup("PATH"), strdup("/usr/bin:/bin"), ENV_VAR, NULL};
	t_env			env = {strdup(""), strdup(""), 0, &env2};
	int				ret;
	int				exp_ret = 0;
	char			*filename = "/tmp/exec_complete_command_unit_valid_basic_piped_command_terminate_first";
	int				fd_out = redirect_std_out(filename);
	char			buffer[1024];
	memset(buffer, 0, 1024);
	cr_assert_gt(fd_out, 0);
	memset(&shell, 0, sizeof(t_shell));
	memset(&job_control, 0, sizeof(t_job_cont));
	shell.job_control = &job_control;
	shell.interactive = true;
	shell.env = &env;
	ret = exec_complete_command(&shell, &command);
	cr_expect_eq(ret, exp_ret, "expected ret %i but got %i!", exp_ret, ret);
	cr_expect_str_eq(shell.env->key, "?");
	cr_expect_str_eq(shell.env->value, "0");
	int	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	close(read_fd);
	cr_expect_not_null(strstr(buffer, "1000\n"));
	close(fd_out);
	dprintf(2, "-");
	fflush(stderr);
	cr_expect_stderr_eq_str("-");
	cr_expect_eq(shell.job_control->current, 0);
	cr_expect_eq(shell.job_control->previous, 0);
	cr_expect_null(shell.job_control->job_list);
}

Test(exec_complete_command_unit, valid_basic_piped_command_background, .init = redirect_std_err_out)
{
	char			**argv2 = ft_strsplit("/bin/cat", ' ');
	char			**argv = ft_strsplit("/bin/echo foo", ' ');
	t_argument		argument21 = {strdup("/bin/cat"), NULL};
	t_argument		argument12 = {strdup("foo"), NULL};
	t_argument		argument11 = {strdup("/bin/echo"), &argument12};
	t_simple_cmd	simple_cmd2 = {NULL, &argument21, argv2};
	t_simple_cmd	simple_cmd = {NULL, &argument11, argv};
	t_pipe_sequence	pipe_seq2 = {&simple_cmd2, "/bin/cat", no_pipe, NULL};
	t_pipe_sequence	pipe_seq = {&simple_cmd, "/bin/echo foo |", pipe_op, &pipe_seq2};
	t_complete_cmd	command = {&pipe_seq, "/bin/echo foo | cat &", background_op, NULL};
	t_shell			shell;
	t_job_cont		job_control;
	t_env			env = {strdup(""), strdup(""), 0, NULL};
	int				ret;
	int				exp_ret = 0;

	memset(&shell, 0, sizeof(t_shell));
	memset(&job_control, 0, sizeof(t_job_cont));
	shell.job_control = &job_control;
	shell.interactive = true;
	shell.env = &env;
	ret = exec_complete_command(&shell, &command);
	cr_expect_eq(ret, exp_ret, "expected ret %i but got %i!", exp_ret, ret);
	cr_expect_str_eq(shell.env->key, "");
	cr_expect_str_eq(shell.env->value, "");
	dprintf(2, "-");
	fflush(stdout);
	cr_expect_stdout_neq_str("foo");
	fflush(stderr);
	cr_expect_stderr_eq_str("-");
	cr_expect_eq(shell.job_control->current, 1);
	cr_expect_eq(shell.job_control->previous, 0);
	cr_assert_not_null(shell.job_control->job_list);
	cr_expect_str_eq(shell.job_control->job_list->command, command.cmd_string);
}

Test(exec_complete_command_unit, valid_basic_command_background, .init = redirect_std_err_out)
{
	char			**argv = ft_strsplit("/bin/echo foo", ' ');
	t_argument		argument2 = {strdup("foo"), NULL};
	t_argument		argument1 = {strdup("/bin/echo"), &argument2};
	t_simple_cmd	simple_cmd = {NULL, &argument1, argv};
	t_pipe_sequence	pipe_seq = {&simple_cmd, "/bin/echo foo", no_pipe, NULL};
	t_complete_cmd	command = {&pipe_seq, "/bin/echo foo &", background_op, NULL};
	t_shell			shell;
	t_job_cont		job_control;
	t_env			env = {strdup(""), strdup(""), 0, NULL};
	int				ret;
	int				exp_ret = 0;

	memset(&shell, 0, sizeof(t_shell));
	memset(&job_control, 0, sizeof(t_job_cont));
	shell.job_control = &job_control;
	shell.interactive = true;
	shell.env = &env;
	ret = exec_complete_command(&shell, &command);
	cr_expect_eq(ret, exp_ret, "expected ret %i but got %i!", exp_ret, ret);
	cr_expect_str_eq(shell.env->key, "");
	cr_expect_str_eq(shell.env->value, "");
	dprintf(2, "-");
	fflush(stdout);
	cr_expect_stdout_neq_str("foo");
	fflush(stderr);
	cr_expect_stderr_eq_str("-");
	cr_expect_eq(shell.job_control->current, 1);
	cr_expect_eq(shell.job_control->previous, 0);
	cr_assert_not_null(shell.job_control->job_list);
	cr_expect_str_eq(shell.job_control->job_list->command, command.cmd_string);
}

Test(exec_complete_command_unit, invalid_basic_command_NULL_shell, .init = redirect_std_err_out)
{
	char			**argv = ft_strsplit("/bin/echo foo", ' ');
	t_argument		argument2 = {strdup("foo"), NULL};
	t_argument		argument1 = {strdup("/bin/echo"), &argument2};
	t_simple_cmd	simple_cmd = {NULL, &argument1, argv};
	t_pipe_sequence	pipe_seq = {&simple_cmd, "/bin/echo foo", no_pipe, NULL};
	t_complete_cmd	command = {&pipe_seq, "/bin/echo foo", no_seperator_op, NULL};
	int				ret;
	int				exp_ret = internal_error;
	char			buff[1024];

	ret = exec_complete_command(NULL, &command);
	cr_expect_eq(ret, exp_ret, "expected ret %i but got %i!", exp_ret, ret);
	printf("-");
	fflush(stdout);
	cr_expect_stdout_eq_str("-");
	fflush(stderr);
	snprintf(buff, 1024, "Cetushell: %s: shell struct is NULL\n", g_error_str[internal_error]);
	cr_expect_stderr_eq_str(buff);
}

Test(exec_complete_command_unit, invalid_empty_simple_cmd, .init = redirect_std_err)
{
	t_simple_cmd	simple_cmd = {NULL, NULL, NULL};
	t_pipe_sequence	pipe_seq = {&simple_cmd, "", no_pipe, NULL};
	t_complete_cmd	command = {&pipe_seq, "", semicolon_op, NULL};
	int				ret;
	int				exp_ret = parsing_error;
	char			buff[1024];
	t_shell			shell;
	t_job_cont		job_control;
	t_env			env = {strdup(""), strdup(""), 0, NULL};

	memset(&shell, 0, sizeof(t_shell));
	memset(&job_control, 0, sizeof(t_job_cont));
	shell.job_control = &job_control;
	shell.interactive = true;
	shell.env = &env;
	ret = exec_complete_command(&shell, &command);
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
	t_shell			shell;
	t_job_cont		job_control;
	t_env			env = {strdup(""), strdup(""), 0, NULL};

	memset(&shell, 0, sizeof(t_shell));
	memset(&job_control, 0, sizeof(t_job_cont));
	shell.job_control = &job_control;
	shell.interactive = true;
	shell.env = &env;
	ret = exec_complete_command(&shell, &command);
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
	t_shell			shell;
	t_job_cont		job_control;
	t_env			env = {strdup(""), strdup(""), 0, NULL};

	memset(&shell, 0, sizeof(t_shell));
	memset(&job_control, 0, sizeof(t_job_cont));
	shell.job_control = &job_control;
	shell.interactive = true;
	shell.env = &env;
	ret = exec_complete_command(&shell, &command);
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
	t_shell			shell;
	t_job_cont		job_control;
	t_env			env = {strdup(""), strdup(""), 0, NULL};

	memset(&shell, 0, sizeof(t_shell));
	memset(&job_control, 0, sizeof(t_job_cont));
	shell.job_control = &job_control;
	shell.interactive = true;
	shell.env = &env;
	ret = exec_complete_command(&shell, NULL);
	cr_expect_eq(ret, exp_ret, "expected ret %i but got %i!", exp_ret, ret);
}
