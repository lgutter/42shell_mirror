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
#include "environment.h"

static void redirect_stdout_err(void)
{
	cr_redirect_stderr();
	cr_redirect_stdout();
}

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

Test(handle_input_integration, basic_run_simple_command_comment, .init = cr_redirect_stdout)
{
	char		*input = "echo foo #COMMENT";
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

Test(handle_input_integration, basic_expand_param, .init = cr_redirect_stdout)
{
	char		*input = "echo ${FOO}";
	char		*expected_output = "SUCCESS\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	ft_setenv(shell->env, "FOO", "SUCCESS", ENV_VAR);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_run_pipe_command, .init = cr_redirect_stdout)
{
	char		*input = "/bin/echo foo |cat -e";
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

Test(handle_input_integration, basic_assignment_word_new_shell_var, .init = cr_redirect_stdout)
{
	char		*input = "basic_assignment_word_new_shell_var=='$PWD';echo $basic_assignment_word_new_shell_var";
	char		*expected_output = "=$PWD\n";

	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_assignment_word_two_new_shell_vars, .init = cr_redirect_stdout)
{
	char		*input = "basic_assignment_word_two_new_shell_vars2=\"foo bar\" basic_assignment_word_two_new_shell_vars1=='$PWD';echo $basic_assignment_word_two_new_shell_vars1 $basic_assignment_word_two_new_shell_vars2";
	char		*expected_output = "=$PWD foo bar\n";

	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_assignment_word_two_vars_restore, .init = redirect_stdout_err)
{
	char		*input = "basic_assignment_word_two_vars_restore=\"foo bar\" OLDPWD==BAR cd -;echo $basic_assignment_word_two_vars_restore $OLDPWD";
	char		*expected_output = " FOO\n";

	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	char		*key = "OLDPWD";
	char		*value = "FOO";
	ft_setenv(shell->env, key, value, ENV_VAR);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
	char	errbuff[1024];
	memset(errbuff, 0, 1024);
	snprintf(errbuff, 1024, "Cetushell: cd: =BAR: %s\n", g_error_str[no_such_file_or_dir]);
	cr_expect_stderr_eq_str(errbuff);
}

Test(handle_input_integration, basic_assignment_word_replace_shell_var, .init = cr_redirect_stdout)
{
	char		*input = "echo $basic_assignment_word_replace_shell_var;basic_assignment_word_replace_shell_var=='$PWD';echo $basic_assignment_word_replace_shell_var";
	char		*expected_output = "FOO\n=$PWD\n";

	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	char		*key = "basic_assignment_word_replace_shell_var";
	char		*value = "FOO";
	ft_setenv(shell->env, key, value, SHELL_VAR);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_assignment_word_replace_var, .init = cr_redirect_stdout)
{
	char		*input = "basic_assignment_word_replace_var=BAR env | grep basic_assignment_word_replace_var;echo $basic_assignment_word_replace_var";
	char		*expected_output = "basic_assignment_word_replace_var=BAR\nFOO\n";

	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	char		*key = "basic_assignment_word_replace_var";
	char		*value = "FOO";
	ft_setenv(shell->env, key, value, ENV_VAR);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
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

Test(handle_input_integration, basic_complete_heredoc_comment, .init = cr_redirect_stdout)
{
	char		*input = "cat <<EOF #COMMENT";
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

Test(handle_input_integration, basic_complete_pipe, .init = cr_redirect_stdout)
{
	char		*input = "echo foo |";
	char		*extra_input = "cat -e";
	char		*expected_output = "foo$\n";

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

Test(handle_input_integration, basic_complete_pipe_comment, .init = cr_redirect_stdout)
{
	char		*input = "echo foo |#COMMENT";
	char		*extra_input = "cat -e";
	char		*expected_output = "foo$\n";

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

Test(handle_input_integration, invalid_invalid_assignment, .init = cr_redirect_stderr)
{
	char		*input = "9FOO=BAR";

	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &buffer);
	char temp[1024];
	memset(temp, 0, 1024);
	snprintf(temp, 1024, "Cetushell: %s: %s\n", g_error_str[cmd_not_found], input);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
}

Test(handle_input_integration, invalid_bad_substitution, .init = cr_redirect_stderr)
{
	char		*input = "echo ${FOO\n";

	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &buffer);
	char temp[1024];
	memset(temp, 0, 1024);
	snprintf(temp, 1024, "Cetushell: %s: ${FOO\n", g_error_str[bad_subst_err]);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
}
