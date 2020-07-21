/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_jobs.spec.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 16:23:35 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/16 16:23:35 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "builtins.h"
#include "handle_input.h"

// int			builtin_jobs(char **argv, t_shell *shell);
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

Test(builtin_jobs_integration, basic_single_job_no_options, .init = cr_redirect_stderr)
{
	char	**argv = ft_strsplit("jobs", ' ');

	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
	t_shell		*shell = init_shell(false);
	cr_assert_not_null(shell);
	shell->job_control = job_control;
	char		*input = strdup("sleep 0.4 | sleep 0.4&");
	char		*filename = "/tmp/builtin_jobs_integration_basic_single_job_no_options";
	int			fd = redirect_std_out(filename);
	char		buffer[1024];

	memset(buffer, 0, 1024);
	cr_assert_gt(fd, 0);
	handle_input(shell, &input);
	int	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	close(read_fd);
	cr_expect_not_null(strstr(buffer, "[1] +"));
	close(fd);


	fd = redirect_std_out(filename);
	int ret = builtin_jobs(shell, argv);
	cr_expect_eq(ret, 0);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_not_null(strstr(buffer, "[1] +"));
	cr_expect_not_null(strstr(buffer, "running"));
	cr_expect_not_null(strstr(buffer, "sleep 0.4 | sleep 0.4 &"));
	cr_expect_eq(job_control->current, 1);
	cr_expect_eq(job_control->previous, 0);
	cr_assert_not_null(job_control->job_list);
	char *pgrp_str = ft_itoa(job_control->job_list->pgrp);
	cr_expect_not_null(strstr(buffer, pgrp_str));
	close(fd);
	close(read_fd);


	fd = redirect_std_out(filename);
	usleep(500000);
	builtin_jobs(shell, argv);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_not_null(strstr(buffer, "[1] +"));
	cr_expect_not_null(strstr(buffer, "exited"));
	cr_expect_not_null(strstr(buffer, "sleep 0.4 | sleep 0.4 &"));
	cr_expect_not_null(strstr(buffer, pgrp_str));
	cr_expect_eq(job_control->current, 0);
	cr_expect_eq(job_control->previous, 0);
	cr_expect_null(job_control->job_list);
	close(fd);
	close(read_fd);


	remove(filename);
	free_job_control(job_control);
}

Test(builtin_jobs_integration, basic_single_job_status_differ_no_options, .init = cr_redirect_stderr)
{
	char	**argv = ft_strsplit("jobs", ' ');

	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
	t_shell		*shell = init_shell(false);
	cr_assert_not_null(shell);
	shell->job_control = job_control;
	char		*input = strdup("/bin/echo foo  | sleep 0.6&");
	char		*filename = "/tmp/builtin_jobs_integration_basic_single_job_status_differ_no_options";
	int			fd = redirect_std_out(filename);
	char		buffer[1024];

	memset(buffer, 0, 1024);
	cr_assert_gt(fd, 0);
	handle_input(shell, &input);
	int	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	close(read_fd);
	cr_expect_not_null(strstr(buffer, "[1] +"));
	close(fd);


	fd = redirect_std_out(filename);
	usleep(100000);
	builtin_jobs(shell, argv);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_not_null(strstr(buffer, "[1] +"));
	cr_expect_not_null(strstr(buffer, "exited     /bin/echo foo |\n"));
	cr_expect_not_null(strstr(buffer, "running    sleep 0.6 &\n"));
	cr_expect_eq(job_control->current, 1);
	cr_expect_eq(job_control->previous, 0);
	cr_assert_not_null(job_control->job_list);
	char *pgrp_str = ft_itoa(job_control->job_list->pgrp);
	cr_expect_not_null(strstr(buffer, pgrp_str));
	close(fd);
	close(read_fd);


	fd = redirect_std_out(filename);
	usleep(600000);
	builtin_jobs(shell, argv);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_not_null(strstr(buffer, "[1] +"));
	cr_expect_not_null(strstr(buffer, "exited     /bin/echo foo | sleep 0.6 &"));
	cr_expect_not_null(strstr(buffer, pgrp_str));
	cr_expect_eq(job_control->current, 0);
	cr_expect_eq(job_control->previous, 0);
	cr_expect_null(job_control->job_list);
	close(fd);
	close(read_fd);


	remove(filename);
	free_job_control(job_control);
}

Test(builtin_jobs_integration, basic_single_job_long_option, .init = cr_redirect_stderr)
{
	char	**argv = ft_strsplit("jobs -l", ' ');

	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
	t_shell		*shell = init_shell(false);
	cr_assert_not_null(shell);
	shell->job_control = job_control;
	char		*input = strdup("sleep 0.4 | sleep 0.5&");
	char		*filename = "/tmp/builtin_jobs_integration_basic_single_job_long_option";
	int			fd = redirect_std_out(filename);
	char		buffer[1024];

	memset(buffer, 0, 1024);
	cr_assert_gt(fd, 0);
	handle_input(shell, &input);
	int	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	close(read_fd);
	cr_expect_not_null(strstr(buffer, "[1] +"));
	close(fd);


	fd = redirect_std_out(filename);
	builtin_jobs(shell, argv);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_not_null(strstr(buffer, "[1] +"));
	cr_expect_not_null(strstr(buffer, "running    sleep 0.4 |\n"));
	cr_expect_not_null(strstr(buffer, "running    sleep 0.5 &\n"));
	cr_expect_eq(job_control->current, 1);
	cr_expect_eq(job_control->previous, 0);
	cr_assert_not_null(job_control->job_list);
	char *pgrp_str = ft_itoa(job_control->job_list->pgrp);
	cr_expect_not_null(strstr(buffer, pgrp_str));
	close(fd);
	close(read_fd);


	fd = redirect_std_out(filename);
	usleep(600000);
	builtin_jobs(shell, argv);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_not_null(strstr(buffer, "[1] +"));
	cr_expect_not_null(strstr(buffer, "exited     sleep 0.4 |\n"));
	cr_expect_not_null(strstr(buffer, "exited     sleep 0.5 &\n"));
	cr_expect_not_null(strstr(buffer, pgrp_str));
	cr_expect_eq(job_control->current, 0);
	cr_expect_eq(job_control->previous, 0);
	cr_expect_null(job_control->job_list);
	close(fd);
	close(read_fd);


	remove(filename);
	free_job_control(job_control);
}

Test(builtin_jobs_integration, basic_single_job_pid_option, .init = cr_redirect_stderr)
{
	char	**argv = ft_strsplit("jobs -p", ' ');

	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
	t_shell		*shell = init_shell(false);
	cr_assert_not_null(shell);
	shell->job_control = job_control;
	char		*input = strdup("sleep 0.4 | sleep 0.5&");
	char		*filename = "/tmp/builtin_jobs_integration_basic_single_job_pid_option";
	int			fd = redirect_std_out(filename);
	char		buffer[1024];

	memset(buffer, 0, 1024);
	cr_assert_gt(fd, 0);
	handle_input(shell, &input);
	int	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	close(read_fd);
	cr_expect_not_null(strstr(buffer, "[1] +"));
	close(fd);


	fd = redirect_std_out(filename);
	builtin_jobs(shell, argv);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_null(strstr(buffer, "[1] +"));
	cr_expect_null(strstr(buffer, "running"));
	cr_expect_null(strstr(buffer, "sleep"));
	cr_expect_eq(job_control->current, 1);
	cr_expect_eq(job_control->previous, 0);
	cr_assert_not_null(job_control->job_list);
	char *pgrp_str = ft_itoa(job_control->job_list->pgrp);
	cr_expect_not_null(strstr(buffer, pgrp_str));
	close(fd);
	close(read_fd);


	fd = redirect_std_out(filename);
	usleep(600000);
	builtin_jobs(shell, argv);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_null(strstr(buffer, "[1] +"));
	cr_expect_null(strstr(buffer, "exited"));
	cr_expect_null(strstr(buffer, "sleep"));
	cr_expect_not_null(strstr(buffer, pgrp_str));
	cr_expect_eq(job_control->current, 1);
	cr_expect_eq(job_control->previous, 0);
	cr_expect_not_null(job_control->job_list);
	close(fd);
	close(read_fd);

	free(argv[1]);
	argv[1] = NULL;
	fd = redirect_std_out(filename);
	builtin_jobs(shell, argv);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_not_null(strstr(buffer, "[1] +"));
	cr_expect_not_null(strstr(buffer, "exited     sleep 0.4 | sleep 0.5 &"));
	cr_expect_not_null(strstr(buffer, pgrp_str));
	cr_expect_eq(job_control->current, 0);
	cr_expect_eq(job_control->previous, 0);
	cr_expect_null(job_control->job_list);
	close(fd);
	close(read_fd);


	remove(filename);
	free_job_control(job_control);
}

Test(builtin_jobs_integration, basic_two_jobs_pid_option, .init = cr_redirect_stderr)
{
	char	**argv = ft_strsplit("jobs -p", ' ');
	char	**argv_no_op = ft_strsplit("jobs", ' ');
	char	**argv_job_spec = ft_strsplit("jobs %?echo", ' ');
	char	**argv_wrong_spec = ft_strsplit("jobs %foo", ' ');

	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
	t_shell		*shell = init_shell(false);
	cr_assert_not_null(shell);
	shell->job_control = job_control;
	char		*input = strdup("/bin/echo| sleep 1.5&");
	char		*input1 = strdup("sleep 0.4 | sleep 0.5&");
	char		*filename = "/tmp/builtin_jobs_integration_basic_two_jobs_pid_option";
	int			fd = redirect_std_out(filename);
	char		buffer[1024];

	memset(buffer, 0, 1024);
	cr_assert_gt(fd, 0);
	handle_input(shell, &input);
	handle_input(shell, &input1);
	int	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	close(read_fd);
	cr_expect_not_null(strstr(buffer, "[1] +"));
	cr_expect_not_null(strstr(buffer, "[2] +"));
	close(fd);

	usleep(100000);

	fd = redirect_std_out(filename);
	builtin_jobs(shell, argv);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_null(strstr(buffer, "[1] +"));
	cr_expect_null(strstr(buffer, "running"));
	cr_expect_null(strstr(buffer, "sleep"));
	cr_expect_null(strstr(buffer, "echo"));
	cr_expect_eq(job_control->current, 2);
	cr_expect_eq(job_control->previous, 1);
	cr_assert_not_null(job_control->job_list);
	char *pgrp_str = ft_itoa(job_control->job_list->pgrp);
	cr_expect_not_null(strstr(buffer, pgrp_str));
	close(fd);
	close(read_fd);

	fd = redirect_std_out(filename);
	builtin_jobs(shell, argv_job_spec);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_not_null(strstr(buffer, "[1] -"));
	cr_expect_not_null(strstr(buffer, "exited     /bin/echo |\n"));
	cr_expect_not_null(strstr(buffer, "running    sleep 1.5 &\n"));
	cr_expect_null(strstr(buffer, "[2]"));
	cr_expect_null(strstr(buffer, "sleep 0.4"));
	cr_expect_eq(job_control->current, 2);
	cr_expect_eq(job_control->previous, 1);
	cr_expect_not_null(job_control->job_list);
	cr_expect_not_null(strstr(buffer, pgrp_str));
	close(fd);
	close(read_fd);

	fd = redirect_std_out(filename);
	builtin_jobs(shell, argv_wrong_spec);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_eq(read(read_fd, buffer, 1024), (ssize_t)0);
	fflush(stderr);
	cr_expect_stderr_eq_str("jobs: job not found: %foo\n");
	cr_expect_eq(job_control->current, 2);
	cr_expect_eq(job_control->previous, 1);
	cr_expect_not_null(job_control->job_list);
	close(fd);
	close(read_fd);

	fd = redirect_std_out(filename);
	builtin_jobs(shell, argv_no_op);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_not_null(strstr(buffer, "[1] -"));
	cr_expect_not_null(strstr(buffer, "exited     /bin/echo |\n"));
	cr_expect_not_null(strstr(buffer, "running    sleep 1.5 &\n"));
	cr_expect_not_null(strstr(buffer, "[2] +"));
	cr_expect_not_null(strstr(buffer, "running    sleep 0.4 | sleep 0.5 &\n"));
	cr_expect_eq(job_control->current, 2);
	cr_expect_eq(job_control->previous, 1);
	cr_expect_not_null(job_control->job_list);
	cr_expect_not_null(strstr(buffer, pgrp_str));
	close(fd);
	close(read_fd);

	usleep(500000);

	fd = redirect_std_out(filename);
	builtin_jobs(shell, argv);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_null(strstr(buffer, "[1] +"));
	cr_expect_null(strstr(buffer, "running"));
	cr_expect_null(strstr(buffer, "sleep"));
	cr_expect_null(strstr(buffer, "echo"));
	cr_expect_eq(job_control->current, 2);
	cr_expect_eq(job_control->previous, 1);
	cr_expect_not_null(job_control->job_list);
	cr_expect_not_null(strstr(buffer, pgrp_str));
	close(fd);
	close(read_fd);

	fd = redirect_std_out(filename);
	builtin_jobs(shell, argv_no_op);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_not_null(strstr(buffer, "[1] -"));
	cr_expect_not_null(strstr(buffer, "exited     /bin/echo |\n"));
	cr_expect_not_null(strstr(buffer, "running    sleep 1.5 &\n"));
	cr_expect_not_null(strstr(buffer, "[2] +"));
	cr_expect_not_null(strstr(buffer, "exited     sleep 0.4 | sleep 0.5 &\n"));
	cr_expect_not_null(strstr(buffer, pgrp_str));
	cr_expect_eq(job_control->current, 1);
	cr_expect_eq(job_control->previous, 0);
	cr_expect_not_null(job_control->job_list);
	close(fd);
	close(read_fd);

	usleep(1000000);

	fd = redirect_std_out(filename);
	builtin_jobs(shell, argv);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_null(strstr(buffer, "[2]"));
	cr_expect_null(strstr(buffer, "running"));
	cr_expect_null(strstr(buffer, "sleep"));
	cr_expect_null(strstr(buffer, "echo"));
	cr_expect_eq(job_control->current, 1);
	cr_expect_eq(job_control->previous, 0);
	cr_expect_not_null(job_control->job_list);
	cr_expect_not_null(strstr(buffer, pgrp_str));
	close(fd);
	close(read_fd);

	fd = redirect_std_out(filename);
	builtin_jobs(shell, argv_no_op);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_null(strstr(buffer, "[2]"));
	cr_expect_null(strstr(buffer, "sleep 0.4"));
	cr_expect_not_null(strstr(buffer, "[1] +"));
	cr_expect_not_null(strstr(buffer, "exited     /bin/echo | sleep 1.5 &\n"));
	cr_expect_not_null(strstr(buffer, pgrp_str));
	cr_expect_eq(job_control->current, 0);
	cr_expect_eq(job_control->previous, 0);
	cr_expect_null(job_control->job_list);
	close(fd);
	close(read_fd);



	remove(filename);
	free_job_control(job_control);
}

Test(builtin_jobs_integration, error_NULL_shell)
{
	char	**argv = ft_strsplit("jobs", ' ');

	t_shell		*shell = NULL;

	int ret = builtin_jobs(shell, argv);
	cr_expect_eq(ret, 1);
}

Test(builtin_jobs_integration, error_NULL_job_control)
{
	char	**argv = ft_strsplit("jobs", ' ');

	t_job_cont	*job_control = NULL;
	t_shell		*shell = init_shell(false);
	shell->job_control = job_control;

	int ret = builtin_jobs(shell, argv);
	cr_expect_eq(ret, 1);
}
