/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_fg.spec.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/21 12:14:37 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/21 12:14:37 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "builtins.h"
#include "handle_input.h"
#include "error_str.h"
#include <signal.h>

// int		builtin_fg(t_shell *shell, char **argv);

Test(builtin_fg_unit, error_null_argv_zero, .init =cr_redirect_stdout)
{
	char	**argv = ft_strsplit("", ' ');
	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
	t_shell		*shell = init_shell(false);
	shell->interactive = true;
	cr_assert_not_null(shell);
	shell->job_control = job_control;

	int ret = builtin_fg(shell, argv);
	cr_expect_eq(ret, 1, "fg did not return error with NULL argv[0]");
}

Test(builtin_fg_unit, error_null_argv, .init =cr_redirect_stdout)
{
	char	**argv = NULL;
	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
	t_shell		*shell = init_shell(false);
	shell->interactive = true;
	cr_assert_not_null(shell);
	shell->job_control = job_control;

	int ret = builtin_fg(shell, argv);
	cr_expect_eq(ret, 1, "fg did not return error with NULL argv[0]");
}

Test(builtin_fg_unit, error_null_job_control, .init =cr_redirect_stdout)
{
	char	**argv = ft_strsplit("jobs", ' ');
	t_job_cont	*job_control = NULL;
	t_shell		*shell = init_shell(false);
	shell->interactive = true;
	cr_assert_not_null(shell);
	shell->job_control = job_control;

	int ret = builtin_fg(shell, argv);
	cr_expect_eq(ret, 1, "fg did not return error with NULL argv[0]");
}

Test(builtin_fg_unit, error_null_shell, .init =cr_redirect_stdout)
{
	char	**argv = ft_strsplit("jobs", ' ');
	t_shell		*shell = NULL;

	int ret = builtin_fg(shell, argv);
	cr_expect_eq(ret, 1, "fg did not return error with NULL argv[0]");
}

Test(builtin_fg_unit, error_job_id_no_job, .init =cr_redirect_stderr)
{
	char	**argv = ft_strsplit("fg %1", ' ');
	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
	t_shell		*shell = init_shell(false);
	shell->interactive = true;
	cr_assert_not_null(shell);
	shell->job_control = job_control;

	cr_expect_eq(1, builtin_fg(shell, argv));
	fflush(stderr);
	char buffer[1024];
	snprintf(buffer, 1024, "Cetushell: fg: %s: %s\n", "%1", g_error_str[job_not_found]);
	cr_expect_stderr_eq_str(buffer);
}

Test(builtin_fg_unit, error_ambig_job, .init =cr_redirect_stderr)
{
	char	**argv = ft_strsplit("fg %sle", ' ');
	t_shell		*shell = init_shell(false);
	shell->interactive = true;
	cr_assert_not_null(shell);
	t_job		*job2 = init_job(shell, "sleep 42", false);
	cr_assert_not_null(job2);
	t_job		*job1 = init_job(shell, "sleep 21", false);
	cr_assert_not_null(job1);
	job1->next = job2;
	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
	cr_assert_not_null(job_control);
	job_control->job_list = job1;
	shell->job_control = job_control;


	cr_expect_eq(1, builtin_fg(shell, argv));
	fflush(stderr);
	char buffer[1024];
	snprintf(buffer, 1024, "Cetushell: fg: %s: %s\n", "%sle", g_error_str[ambig_job_spec]);
	cr_expect_stderr_eq_str(buffer);
}
