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
#include <signal.h>

static void redirect_std_out()
{
	cr_redirect_stdout();
}

static void redirect_std_err()
{
	cr_redirect_stderr();
}

static void redirect_std_err_out()
{
	cr_redirect_stderr();
	cr_redirect_stdout();
}

Test(exec_simple_command_unit, valid_basic_command, .init = redirect_std_out)
{
	char			**argv = ft_strsplit("/bin/echo foo", ' ');
	t_argument		argument2 = {strdup("foo"), NULL};
	t_argument		argument1 = {strdup("/bin/echo"), &argument2};
	t_simple_cmd	simple_cmd = {NULL, &argument1, argv};
	t_shell			shell;
	int				ret;
	int				exp_ret = 0;

	memset(&shell, 0, sizeof(t_shell));
	shell.env = dup_sys_env();
	pid_t	pid = fork();
	if (pid == 0)
		exit(exec_simple_command(&simple_cmd, &shell));
	else if (pid > 0)
	{
		pid_t shell_pid = tcgetpgrp(STDIN_FILENO);
		setpgid (pid, pid);
		tcsetpgrp(STDIN_FILENO, pid);
		int stat_loc;
		waitpid(pid, &stat_loc, 0);
		ret = (int)WEXITSTATUS(stat_loc);
		tcsetpgrp(STDIN_FILENO, shell_pid);
		cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
		fflush(stdout);
		cr_expect_stdout_eq_str("foo\n");
	}
}

Test(exec_simple_command_unit, valid_basic_builtin, .init = redirect_std_out)
{
	char			**argv = ft_strsplit("echo foo", ' ');
	t_argument		argument2 = {strdup(argv[1]), NULL};
	t_argument		argument1 = {strdup(argv[0]), &argument2};
	t_simple_cmd	simple_cmd = {NULL, &argument1, argv};
	t_shell			shell;
	int				ret;
	int				exp_ret = 0;

	memset(&shell, 0, sizeof(t_shell));
	shell.env = dup_sys_env();
	pid_t	pid = fork();
	if (pid == 0)
		exit(exec_simple_command(&simple_cmd, &shell));
	else if (pid > 0)
	{
		pid_t shell_pid = tcgetpgrp(STDIN_FILENO);
		setpgid (pid, pid);
		tcsetpgrp(STDIN_FILENO, pid);
		int stat_loc;
		waitpid(pid, &stat_loc, 0);
		ret = (int)WEXITSTATUS(stat_loc);
		tcsetpgrp(STDIN_FILENO, shell_pid);
		cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
		fflush(stdout);
		cr_expect_stdout_eq_str("foo\n");
	}
}

Test(exec_simple_command_unit, invalid_is_dir, .init = redirect_std_err)
{
	char			**argv = ft_strsplit("/tmp foo", ' ');
	t_argument		argument2 = {strdup("foo"), NULL};
	t_argument		argument1 = {strdup("/tmp"), &argument2};
	t_simple_cmd	simple_cmd = {NULL, &argument1, argv};
	t_shell			shell;
	int				ret;
	int				exp_ret = is_dir_error;
	char			buff[1024];

	memset(&shell, 0, sizeof(t_shell));
	shell.env = dup_sys_env();
	pid_t	pid = fork();
	if (pid == 0)
		exit(exec_simple_command(&simple_cmd, &shell));
	else if (pid > 0)
	{
		pid_t shell_pid = tcgetpgrp(STDIN_FILENO);
		setpgid (pid, pid);
		tcsetpgrp(STDIN_FILENO, pid);
		int stat_loc;
		waitpid(pid, &stat_loc, 0);
		ret = (int) WEXITSTATUS(stat_loc);
		tcsetpgrp(STDIN_FILENO, shell_pid);
		cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
		fflush(stderr);
		sprintf(buff, "Cetushell: %s: %s\n", g_error_str[exp_ret], argv[0]);
		cr_expect_stderr_eq_str(buff);
	}
}

Test(exec_simple_command_unit, invalid_does_not_exist, .init = redirect_std_err)
{
	char			**argv = ft_strsplit("/tmp/thisfiledoesnotexist foo", ' ');
	t_argument		argument2 = {strdup(argv[1]), NULL};
	t_argument		argument1 = {strdup(argv[0]), &argument2};
	t_simple_cmd	simple_cmd = {NULL, &argument1, argv};
	t_shell			shell;
	int				ret;
	int				exp_ret = no_such_file_or_dir;
	char			buff[1024];

	memset(&shell, 0, sizeof(t_shell));
	shell.env = dup_sys_env();
	pid_t	pid = fork();
	if (pid == 0)
		exit(exec_simple_command(&simple_cmd, &shell));
	else if (pid > 0)
	{
		pid_t shell_pid = tcgetpgrp(STDIN_FILENO);
		setpgid (pid, pid);
		tcsetpgrp(STDIN_FILENO, pid);
		int stat_loc;
		waitpid(pid, &stat_loc, 0);
		ret = (int) WEXITSTATUS(stat_loc);
		tcsetpgrp(STDIN_FILENO, shell_pid);
		cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
		fflush(stderr);
		sprintf(buff, "Cetushell: %s: %s\n", g_error_str[exp_ret], argv[0]);
		cr_expect_stderr_eq_str(buff);
	}
}

Test(exec_simple_command_unit, invalid_no_exec_perm, .init = redirect_std_err)
{
	char			**argv = ft_strsplit("/tmp/no_exec_perm foo", ' ');
	t_argument		argument2 = {strdup(argv[1]), NULL};
	t_argument		argument1 = {strdup(argv[0]), &argument2};
	t_simple_cmd	simple_cmd = {NULL, &argument1, argv};
	t_shell			shell;
	int				ret;
	int				exp_ret = access_denied;
	char			buff[1024];

	remove(argv[0]);
	int fd = open(argv[0], O_RDONLY | O_CREAT, 0444);

		memset(&shell, 0, sizeof(t_shell));
		shell.env = dup_sys_env();close(fd);
	pid_t	pid = fork();
	if (pid == 0)
		exit(exec_simple_command(&simple_cmd, &shell));
	else if (pid > 0)
	{
		pid_t shell_pid = tcgetpgrp(STDIN_FILENO);
		setpgid (pid, pid);
		tcsetpgrp(STDIN_FILENO, pid);
		int stat_loc;
		waitpid(pid, &stat_loc, 0);
		ret = (int) WEXITSTATUS(stat_loc);
		tcsetpgrp(STDIN_FILENO, shell_pid);
		cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
		fflush(stderr);
		sprintf(buff, "Cetushell: %s: %s\n", g_error_str[exp_ret], argv[0]);
		cr_expect_stderr_eq_str(buff);
		remove(argv[0]);
	}
}

Test(exec_simple_command_unit, valid_NULL_env, .init = redirect_std_err_out)
{
	char			**argv = ft_strsplit("/bin/echo foo", ' ');
	t_argument		argument2 = {strdup("foo"), NULL};
	t_argument		argument1 = {strdup("/bin/echo"), &argument2};
	t_simple_cmd	simple_cmd = {NULL, &argument1, argv};
	t_shell			shell;
	int				ret;
	int				exp_ret = 0;
	// char			buff[1024];

	memset(&shell, 0, sizeof(t_shell));
	pid_t	pid = fork();
	if (pid == 0)
		exit(exec_simple_command(&simple_cmd, &shell));
	else if (pid > 0)
	{
		pid_t shell_pid = tcgetpgrp(STDIN_FILENO);
		setpgid (pid, pid);
		tcsetpgrp(STDIN_FILENO, pid);
		int stat_loc;
		waitpid(pid, &stat_loc, 0);
		ret = (int) WEXITSTATUS(stat_loc);
		tcsetpgrp(STDIN_FILENO, shell_pid);
		write(STDERR_FILENO, "-", 1);
		cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
		fflush(stdout);
		cr_expect_stdout_eq_str("foo\n");
		fflush(stderr);
		// sprintf(buff, "Cetushell: %s\n", g_error_str[env_empty_error]);
		cr_expect_stderr_eq_str("-");
	}
}

Test(exec_simple_command_unit, invalid_NULL_argv)
{
	char			**argv = NULL;
	t_argument		argument2 = {strdup("foo"), NULL};
	t_argument		argument1 = {strdup("/bin/echo"), &argument2};
	t_simple_cmd	simple_cmd = {NULL, &argument1, argv};
	t_shell			shell;
	int				ret;
	int				exp_ret = parsing_error;

	memset(&shell, 0, sizeof(t_shell));
	shell.env = dup_sys_env();
	pid_t	pid = fork();
	if (pid == 0)
		exit(exec_simple_command(&simple_cmd, &shell));
	else if (pid > 0)
	{
		pid_t shell_pid = tcgetpgrp(STDIN_FILENO);
		setpgid (pid, pid);
		tcsetpgrp(STDIN_FILENO, pid);
		int stat_loc;
		waitpid(pid, &stat_loc, 0);
		ret = (int) WEXITSTATUS(stat_loc);
		tcsetpgrp(STDIN_FILENO, shell_pid);
		cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
	}
}

Test(exec_simple_command_unit, invalid_NULL_argv_zero)
{
	char			*argv_zero = NULL;
	t_argument		argument2 = {strdup("foo"), NULL};
	t_argument		argument1 = {strdup("/bin/echo"), &argument2};
	t_simple_cmd	simple_cmd = {NULL, &argument1, &argv_zero};
	t_shell			shell;
	int				ret;
	int				exp_ret = parsing_error;

	memset(&shell, 0, sizeof(t_shell));
	shell.env = dup_sys_env();
	pid_t	pid = fork();
	if (pid == 0)
		exit(exec_simple_command(&simple_cmd, &shell));
	else if (pid > 0)
	{
		pid_t shell_pid = tcgetpgrp(STDIN_FILENO);
		setpgid (pid, pid);
		tcsetpgrp(STDIN_FILENO, pid);
		int stat_loc;
		waitpid(pid, &stat_loc, 0);
		ret = (int) WEXITSTATUS(stat_loc);
		tcsetpgrp(STDIN_FILENO, shell_pid);
		cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
	}
}

Test(exec_simple_command_unit, invalid_empty_simple_cmd)
{
	t_simple_cmd	simple_cmd = {NULL, NULL, NULL};
	t_shell			shell;
	int				ret;
	int				exp_ret = parsing_error;

	memset(&shell, 0, sizeof(t_shell));
	shell.env = dup_sys_env();
	pid_t	pid = fork();
	if (pid == 0)
		exit(exec_simple_command(&simple_cmd, &shell));
	else if (pid > 0)
	{
		pid_t shell_pid = tcgetpgrp(STDIN_FILENO);
		setpgid (pid, pid);
		tcsetpgrp(STDIN_FILENO, pid);
		int stat_loc;
		waitpid(pid, &stat_loc, 0);
		ret = (int)WEXITSTATUS(stat_loc);
		tcsetpgrp(STDIN_FILENO, shell_pid);
		cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
	}
}

Test(exec_simple_command_unit, invalid_NULL_simple_cmd)
{
	t_shell			shell;
	int				ret;
	int				exp_ret = parsing_error;

	memset(&shell, 0, sizeof(t_shell));
	shell.env = dup_sys_env();
	signal(SIGCHLD, SIG_DFL);
	pid_t	pid = fork();
	if (pid == 0)
		exit(exec_simple_command(NULL, &shell));
	else if (pid > 0)
	{
		pid_t shell_pid = tcgetpgrp(STDIN_FILENO);
		setpgid (pid, pid);
		tcsetpgrp(STDIN_FILENO, pid);
		int stat_loc;
		waitpid(pid, &stat_loc, 0);
		ret = (int)WEXITSTATUS(stat_loc);
		tcsetpgrp(STDIN_FILENO, shell_pid);
		cr_expect_eq(ret, exp_ret, "expected ret %i, got %i!", exp_ret, ret);
	}
}
