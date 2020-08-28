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

Test(handle_input_integration, basic_run_and_or_commands_fail_first, .init = cr_redirect_stdout)
{
	char		*input = "false && echo foo || echo bar";
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

Test(handle_input_integration, basic_run_and_or_commands_multiple_fail_first, .init = cr_redirect_stdout)
{
	char		*input = "false && echo foo && echo oof || echo bar";
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

Test(handle_input_integration, basic_run_or_and_commands_succeed_first, .init = cr_redirect_stdout)
{
	char		*input = "true || echo foo && echo bar";
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

Test(handle_input_integration, basic_run_or_and_commands_multiple_succeed_first, .init = cr_redirect_stdout)
{
	char		*input = "true || echo foo || echo oof && echo bar";
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

Test(handle_input_integration, basic_arithmetic_number, .init = cr_redirect_stdout)
{
	char		*input = "echo $((42))";
	char		*expected_output = "42\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_addition, .init = cr_redirect_stdout)
{
	char		*input = "echo $((1+2))";
	char		*expected_output = "3\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_substraction, .init = cr_redirect_stdout)
{
	char		*input = "echo $((1-2))";
	char		*expected_output = "-1\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_multiple, .init = cr_redirect_stdout)
{
	char		*input = "echo $((1+1))$((2+2))$((3+3))";
	char		*expected_output = "246\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_multiple_nested, .init = cr_redirect_stdout)
{
	char		*input = "echo $(($((1+1))$((2+2))$((3+3)) * $((5 / 5))))";
	char		*expected_output = "246\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_expansion, .init = cr_redirect_stdout)
{
	char		*input = "a=1+1; echo $((${a}))";
	char		*expected_output = "2\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_crementation, .init = cr_redirect_stdout)
{
	char		*input = "b=4; echo $((b++)) $((++b)) $((--b)) $((b--))";
	char		*expected_output = "4 6 5 5\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_crementation_expression, .init = cr_redirect_stdout)
{
	char		*input = "b=4; echo $((1 + b++)) $((++b - 1)) $((--b + 2 / 2)) $((b-- * 2)) $b";
	char		*expected_output = "5 5 6 10 4\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_harder_expression, .init = cr_redirect_stdout)
{
	char		*input = "echo $((65536 * 256 / 1024 % 2147483648))";
	char		*expected_output = "16384\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_comparison, .init = cr_redirect_stdout)
{
	char		*input = "echo $((2<3>0<=1>=2==0!=1))";
	char		*expected_output = "0\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_comparison_expression_expansion, .init = cr_redirect_stdout)
{
	char		*input = "c=8; echo $((123<=123 && 42%42 || c++ + 34))";
	char		*expected_output = "1\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_empty_var, .init = cr_redirect_stdout)
{
	char		*input = "var=; echo $((var))";
	char		*expected_output = "0\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_early_empty_var, .init = cr_redirect_stdout)
{
	char		*input = "var=; echo $(($var))";
	char		*expected_output = "0\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_env_entiresum, .init = cr_redirect_stdout)
{
	char		*input = "var='4 + 4'; echo $(($var))";
	char		*expected_output = "8\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_env_flip, .init = cr_redirect_stdout)
{
	char		*input = "var=1; echo $((- - - - - - -var))";
	char		*expected_output = "-1\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_env_flip_but_the_other_way_around, .init = cr_redirect_stdout)
{
	char		*input = "var=-1; echo $((- - - - - - -var))";
	char		*expected_output = "1\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_env_hex, .init = cr_redirect_stdout)
{
	char		*input = "var=0x111; echo $((var))";
	char		*expected_output = "273\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}


Test(handle_input_integration, basic_arithmetic_env_oct, .init = cr_redirect_stdout)
{
	char		*input = "var=0111; echo $((var))";
	char		*expected_output = "73\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_quintplus, .init = cr_redirect_stdout)
{
	char		*input = "one=1 two=2; echo $((one+++++two)) $one $two";
	char		*expected_output = "4 2 3\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, basic_arithmetic_quintsub, .init = cr_redirect_stdout)
{
	char		*input = "one=1 two=2; echo $((one-----two)) $one $two";
	char		*expected_output = "0 0 1\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, arithmatic_nested, .init = cr_redirect_stdout)
{
	char		*input = "echo $((4 * $((2 + 2))))\n";
	char		*expected_output = "16\n";



	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &input);
	cr_expect_str_eq(buffer, input);
	fflush(stdout);
	cr_expect_stdout_eq_str(expected_output);
}

Test(handle_input_integration, arithmatic_non_numerical_env, .init = cr_redirect_stderr)
{
	char		*input = "var=bla ; echo $((var))\n";

	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &buffer);
	char temp[1024];
	memset(temp, 0, 1024);
	snprintf(temp, 1024, "not a valid number: bla\nCetushell: %s\n", g_error_str[parsing_error]);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
}

Test(handle_input_integration, arithmatic_non_numerical_suffix_env, .init = cr_redirect_stderr)
{
	char		*input = "var=12bla ; echo $((var))\n";

	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &buffer);
	char temp[1024];
	memset(temp, 0, 1024);
	snprintf(temp, 1024, "not a valid number: 12bla\nCetushell: %s\n", g_error_str[parsing_error]);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
}

Test(handle_input_integration, arithmatic_unterminated, .init = cr_redirect_stderr)
{
	char		*input = "echo $(()\n";

	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &buffer);
	char temp[1024];
	memset(temp, 0, 1024);
	snprintf(temp, 1024, "Cetushell: %s\n", g_error_str[bad_subst_err]);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
}

Test(handle_input_integration, arithmatic_double_the_fun_doublewrong, .init = cr_redirect_stderr)
{
	char		*input = "echo $((2 2))\n";

	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &buffer);
	char temp[1024];
	memset(temp, 0, 1024);
	snprintf(temp, 1024, "Cetushell: %s: in arithmetic expansion\n", g_error_str[parsing_error]);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
}

Test(handle_input_integration, arithmatic_missing_operator, .init = cr_redirect_stderr)
{
	char		*input = "echo $((2++2))\n";

	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &buffer);
	char temp[1024];
	memset(temp, 0, 1024);
	snprintf(temp, 1024, "Cetushell: %s: lvalue required\n", g_error_str[bad_math]);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
}

Test(handle_input_integration, arithmatic_too_much_incrementing, .init = cr_redirect_stderr)
{
	char		*input = "var=1; echo $((++var++))\n";

	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &buffer);
	char temp[1024];
	memset(temp, 0, 1024);
	snprintf(temp, 1024, "Cetushell: %s: lvalue required\n", g_error_str[bad_math]);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
}

Test(handle_input_integration, arithmatic_leftover_incrementer, .init = cr_redirect_stderr)
{
	char		*input = "var=1; echo $((++ ++var))\n";

	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &buffer);
	char temp[1024];
	memset(temp, 0, 1024);
	snprintf(temp, 1024, "Cetushell: %s: lvalue required\n", g_error_str[bad_math]);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
}

Test(handle_input_integration, arithmatic_prefix_operator, .init = cr_redirect_stderr)
{
	char		*input = "echo $((*var))\n";

	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &buffer);
	char temp[1024];
	memset(temp, 0, 1024);
	snprintf(temp, 1024, "Cetushell: %s: unexpected operator\n", g_error_str[bad_math]);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
}

Test(handle_input_integration, arithmatic_invalid_operator, .init = cr_redirect_stderr)
{
	char		*input = "echo $((!!!!))\n";

	t_shell		*shell = init_shell(false);
	char		*buffer = strdup(input);
	cr_assert_not_null(shell);
	cr_assert_not_null(buffer);
	handle_input(shell, &buffer);
	char temp[1024];
	memset(temp, 0, 1024);
	snprintf(temp, 1024, "Cetushell: %s: in arithmetic expansion\n", g_error_str[parsing_error]);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
}
