/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_bg.spec.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/21 12:14:37 by lgutter       #+#    #+#                 */
/*   Updated: 2020/08/04 16:45:44 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "builtins.h"
#include "handle_input.h"
#include "error_str.h"
#include <signal.h>

// int		builtin_bg(t_shell *shell, char **argv);

Test(builtin_bg_unit, error_null_argv_zero, .init =cr_redirect_stdout)
{
	char	**argv = ft_strsplit("", ' ');
	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
	t_shell		*shell = init_shell(false);
	cr_assert_not_null(shell);
	shell->job_control = job_control;

	int ret = builtin_bg(shell, argv);
	cr_expect_eq(ret, 1, "bg did not return error with NULL argv[0]");
}

Test(builtin_bg_unit, error_null_argv, .init =cr_redirect_stdout)
{
	char	**argv = NULL;
	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
	t_shell		*shell = init_shell(false);
	cr_assert_not_null(shell);
	shell->job_control = job_control;

	int ret = builtin_bg(shell, argv);
	cr_expect_eq(ret, 1, "bg did not return error with NULL argv[0]");
}

Test(builtin_bg_unit, error_null_job_control, .init =cr_redirect_stdout)
{
	char	**argv = ft_strsplit("jobs", ' ');
	t_job_cont	*job_control = NULL;
	t_shell		*shell = init_shell(false);
	cr_assert_not_null(shell);
	shell->job_control = job_control;

	int ret = builtin_bg(shell, argv);
	cr_expect_eq(ret, 1, "bg did not return error with NULL argv[0]");
}

Test(builtin_bg_unit, error_null_shell, .init =cr_redirect_stdout)
{
	char	**argv = ft_strsplit("jobs", ' ');
	t_shell		*shell = NULL;

	int ret = builtin_bg(shell, argv);
	cr_expect_eq(ret, 1, "bg did not return error with NULL argv[0]");
}

Test(builtin_bg_unit, error_job_id_no_job, .init =cr_redirect_stderr)
{
	char	**argv = ft_strsplit("bg %1", ' ');
	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
	t_shell		*shell = init_shell(false);
	cr_assert_not_null(shell);
	shell->job_control = job_control;

	cr_expect_eq(1, builtin_bg(shell, argv));
	fflush(stderr);
	char buffer[1024];
	snprintf(buffer, 1024, "Cetushell: bg: %s: %s\n", "%1", g_error_str[job_not_found]);
	cr_expect_stderr_eq_str(buffer);
}

Test(builtin_bg_unit, basic_no_args_current_job, .init =cr_redirect_stdout)
{
	char	**argv = ft_strsplit("bg", ' ');
	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
	t_shell		*shell = init_shell(false);
	cr_assert_not_null(shell);
	shell->job_control = job_control;
	char		*input = strdup("sleep 0.5&");
	handle_input(shell, &input);

	t_job *job = shell->job_control->job_list;
	cr_assert_not_null(job, "job was not started!");
	kill(-(job->pgrp), SIGTSTP);
	int stat_loc;
	usleep(100000);
	cr_expect_eq(0, builtin_bg(shell, argv));
	pid_t ret = waitpid(job->pgrp, &stat_loc, WNOHANG | WCONTINUED);
	cr_expect_eq(ret, job->pgrp, "job was not continued by bg!");
	usleep(600000);
	while ((ret = waitpid(job->pgrp, &stat_loc, WNOHANG)) == 0);
	cr_expect_eq(ret, job->pgrp, "job did not exit!, ret: %i", ret);
}

Test(builtin_bg_unit, basic_match_all_jobs, .init =cr_redirect_stdout)
{
	if (getenv("COVERAGE_ENABLED") != NULL)
		cr_skip_test("Test could hang when coverage is enabled, so disabled.");
	char	**argv = ft_strsplit("bg %slee", ' ');
	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
	t_shell		*shell = init_shell(false);
	cr_assert_not_null(shell);
	shell->job_control = job_control;
	char		*input = strdup("sleep 0.5&");
	handle_input(shell, &input);
	handle_input(shell, &input);

	t_job *job = shell->job_control->job_list;
	cr_assert_not_null(job, "job was not started!");
	t_job	*job2 = job->next;
	cr_assert_not_null(job2, "second job was not started!");
	kill(-(job->pgrp), SIGTSTP);
	kill(-(job2->pgrp), SIGTSTP);
	int stat_loc;
	usleep(100000);
	cr_expect_eq(0, builtin_bg(shell, argv));
	pid_t ret = waitpid(job->pgrp, &stat_loc, WNOHANG | WCONTINUED);
	cr_expect_eq(ret, job->pgrp, "job was not continued by bg!");
	ret = waitpid(job2->pgrp, &stat_loc, WNOHANG | WCONTINUED);
	cr_expect_eq(ret, job2->pgrp, "second job was not continued by bg!");
	usleep(600000);
	ret = waitpid(job->pgrp, &stat_loc, WNOHANG);
	cr_expect_eq(ret, job->pgrp, "job did not exit!, ret: %i", ret);
	ret = waitpid(job2->pgrp, &stat_loc, WNOHANG);
	cr_expect_eq(ret, job2->pgrp, "second job did not exit!, ret: %i", ret);
}

Test(builtin_bg_unit, basic_match_two_jobs, .init =cr_redirect_stdout)
{
	#ifdef __linux
		if (getenv("COVERAGE_ENABLED") != NULL)
			cr_skip_test("Test could hang when coverage is enabled, so disabled.");
		char	**argv = ft_strsplit("bg %?0.5", ' ');
		t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
		t_shell		*shell = init_shell(false);
		cr_assert_not_null(shell);
		shell->job_control = job_control;
		char		*input = strdup("sleep 0.5&");
		char		*input2 = strdup("sleep 0.4&");
		handle_input(shell, &input);
		handle_input(shell, &input2);
		handle_input(shell, &input);

		t_job *job = shell->job_control->job_list;
		cr_assert_not_null(job, "job was not started!");
		t_job	*job2 = job->next;
		cr_assert_not_null(job2, "second job was not started!");
		t_job	*job3 = job2->next;
		cr_assert_not_null(job3, "third job was not started!");
		kill(-(job->pgrp), SIGTSTP);
		kill(-(job2->pgrp), SIGTSTP);
		kill(-(job3->pgrp), SIGTSTP);
		int stat_loc;
		usleep(100000);
		cr_expect_eq(0, builtin_bg(shell, argv));
		pid_t ret = waitpid(job->pgrp, &stat_loc, WNOHANG | WCONTINUED);
		cr_expect_eq(ret, job->pgrp, "job was not continued by bg!");
		ret = waitpid(job2->pgrp, &stat_loc, WNOHANG | WCONTINUED);
		cr_expect_eq(ret, 0, "second job was continued by bg, but should not have been!");
		ret = waitpid(job3->pgrp, &stat_loc, WNOHANG | WCONTINUED);
		cr_expect_eq(ret, job3->pgrp, "third job was not continued by bg!");
		usleep(600000);
		ret = waitpid(job->pgrp, &stat_loc, WNOHANG);
		cr_expect_eq(ret, job->pgrp, "job did not exit!, ret: %i", ret);
		ret = waitpid(job2->pgrp, &stat_loc, WNOHANG);
		cr_expect_eq(ret, 0, "second job exited, but should not have been continued!, ret: %i", ret);
		ret = waitpid(job3->pgrp, &stat_loc, WNOHANG);
		cr_expect_eq(ret, job3->pgrp, "job did not exit!, ret: %i", ret);
	#else
		cr_skip_test("Test builtin_bg_unit-basic_match_two_jobs can not be run on MacOS and will be skipped");
	#endif
	}
