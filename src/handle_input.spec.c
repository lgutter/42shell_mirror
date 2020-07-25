/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_input.spec.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 18:49:00 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/15 18:49:00 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/assert.h>
#include "handle_input.h"
#include "cetushell.h"
#include "error_str.h"

Test(handle_input_integration, basic_run_simple_command, .init = cr_redirect_stdout)
{
	char		*input = "/bin/echo foo";
	char		*expected_output = "foo\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_run_pipe_command, .init = cr_redirect_stdout)
{
	char		*input = "/bin/echo foo | cat -e";
	char		*expected_output = "foo$\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_run_and_commands_success, .init = cr_redirect_stdout)
{
	char		*input = "echo foo && echo bar";
	char		*expected_output = "foo\nbar\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_run_or_commands_success, .init = cr_redirect_stdout)
{
	char		*input = "echo foo || echo bar";
	char		*expected_output = "foo\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_run_and_commands_fail, .init = cr_redirect_stdout)
{
	char		*input = "echo foo && false && echo bar";
	char		*expected_output = "foo\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_run_or_commands_fail, .init = cr_redirect_stdout)
{
	char		*input = "false || echo bar";
	char		*expected_output = "bar\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_run_and_or_commands_fail, .init = cr_redirect_stdout)
{
	char		*input = "echo foo && false || echo bar";
	char		*expected_output = "foo\nbar\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_run_pipe_command_background, .init = cr_redirect_stdout)
{
	char		*input = "/bin/echo foo | cat -e &";
	char		*expected_output = "foo$\n";

	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	usleep(50000);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_complete_heredoc, .init = cr_redirect_stdout)
{
	char		*input = "cat <<EOF";
	char		*extra_input = "foo\nbar\nEOF\n";
	char		*expected_output = "foo\nbar\n";

	int			pipe_fd[2];
	cr_assert_eq(0, pipe(pipe_fd), "pipe failed in setup");
	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	cr_assert_eq((ssize_t)strlen(extra_input), write(pipe_fd[1], extra_input, strlen(extra_input)));
	cr_assert_eq(STDIN_FILENO, dup2(pipe_fd[0], STDIN_FILENO), "dup2 failed in setup");
	close(pipe_fd[1]);
	handle_input(shell, &buffer);
	close(pipe_fd[0]);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_complete_heredoc_quoted_here_end, .init = cr_redirect_stdout)
{
	char		*input = "cat <<'EOF'";
	char		*extra_input = "foo\n$PWD\nEOF\n";
	char		*expected_output = "foo\n$PWD\n";

	int			pipe_fd[2];
	cr_assert_eq(0, pipe(pipe_fd), "pipe failed in setup");
	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	cr_assert_eq((ssize_t)strlen(extra_input), write(pipe_fd[1], extra_input, strlen(extra_input)));
	cr_assert_eq(STDIN_FILENO, dup2(pipe_fd[0], STDIN_FILENO), "dup2 failed in setup");
	close(pipe_fd[1]);
	handle_input(shell, &buffer);
	close(pipe_fd[0]);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_complete_dquote, .init = cr_redirect_stdout)
{
	char		*input = "/bin/echo \"hel\\";
	char		*extra_input = "lo world\"";
	char		*expected_output = "hello world\n";

	int			pipe_fd[2];
	cr_assert_eq(0, pipe(pipe_fd), "pipe failed in setup");
	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	cr_assert_eq((ssize_t)strlen(extra_input), write(pipe_fd[1], extra_input, strlen(extra_input)));
	cr_assert_eq(STDIN_FILENO, dup2(pipe_fd[0], STDIN_FILENO), "dup2 failed in setup");
	close(pipe_fd[1]);
	handle_input(shell, &buffer);
	close(pipe_fd[0]);
	char temp[1024];
	memset(temp, 0, 1024);
	snprintf(temp, 1024, "%s\n%s", input, extra_input);
	cr_expect_str_eq(buffer, temp);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_complete_squote, .init = cr_redirect_stdout)
{
	char		*input = "/bin/echo 'hel\\";
	char		*extra_input = "lo world'";
	char		*expected_output = "hel\\\nlo world\n";

	int			pipe_fd[2];
	cr_assert_eq(0, pipe(pipe_fd), "pipe failed in setup");
	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	cr_assert_eq((ssize_t)strlen(extra_input), write(pipe_fd[1], extra_input, strlen(extra_input)));
	cr_assert_eq(STDIN_FILENO, dup2(pipe_fd[0], STDIN_FILENO), "dup2 failed in setup");
	close(pipe_fd[1]);
	handle_input(shell, &buffer);
	close(pipe_fd[0]);
	char temp[1024];
	memset(temp, 0, 1024);
	snprintf(temp, 1024, "%s\n%s", input, extra_input);
	cr_expect_str_eq(buffer, temp);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_complete_backslash, .init = cr_redirect_stdout)
{
	char		*input = "/bin/echo hel\\";
	char		*extra_input = "\"lo world\"";
	char		*expected_output = "hello world\n";

	int			pipe_fd[2];
	cr_assert_eq(0, pipe(pipe_fd), "pipe failed in setup");
	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	cr_assert_eq((ssize_t)strlen(extra_input), write(pipe_fd[1], extra_input, strlen(extra_input)));
	cr_assert_eq(STDIN_FILENO, dup2(pipe_fd[0], STDIN_FILENO), "dup2 failed in setup");
	close(pipe_fd[1]);
	handle_input(shell, &buffer);
	close(pipe_fd[0]);
	char temp[1024];
	memset(temp, 0, 1024);
	snprintf(temp, 1024, "%s\n%s", input, extra_input);
	cr_expect_str_eq(buffer, temp);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, invalid_incomplete_squote, .init = cr_redirect_stderr)
{
	char		*input = "/bin/echo 'hel\\";
	char		*extra_input = "lo world";

	int			pipe_fd[2];
	cr_assert_eq(0, pipe(pipe_fd), "pipe failed in setup");
	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	cr_assert_eq((ssize_t)strlen(extra_input), write(pipe_fd[1], extra_input, strlen(extra_input)));
	cr_assert_eq(STDIN_FILENO, dup2(pipe_fd[0], STDIN_FILENO), "dup2 failed in setup");
	close(pipe_fd[1]);
	handle_input(shell, &buffer);
	close(pipe_fd[0]);
	char temp[1024];
	memset(temp, 0, 1024);
	snprintf(temp, 1024, "%s\n%s\n", input, extra_input);
	cr_expect_str_eq(buffer, temp);
	memset(temp, 0, 1024);
	snprintf(temp, 1024, "Cetushell: %s: unexpected EOF\n", g_error_str[parsing_error]);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
}
