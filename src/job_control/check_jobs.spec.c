/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_jobs.spec.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 12:37:22 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/16 12:37:22 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <sys/types.h>
#include "job_control.h"
#include "handle_input.h"

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

Test(check_jobs_unit, basic_no_children)
{
	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));

	check_jobs(job_control);
	cr_expect_eq(job_control->current, 0);
	cr_expect_eq(job_control->previous, 0);
	cr_expect_null(job_control->job_list);
	free_job_control(job_control);
}

Test(check_jobs_unit, basic_one_child_change)
{
	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
	t_shell		*shell = init_shell(false);
	cr_assert_not_null(shell);
	shell->job_control = job_control;
	char		*input = strdup("sleep 0.4 &");
	char		*filename = "/tmp/check_jobs_unit_basic_one_child_change";
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
	check_jobs(job_control);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_eq(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_eq(job_control->current, 1);
	cr_expect_eq(job_control->previous, 0);
	cr_expect_not_null(job_control->job_list);
	close(read_fd);
	close(fd);
	fd = redirect_std_out(filename);
	usleep(500000);
	check_jobs(job_control);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_not_null(strstr(buffer, "[1] +"));
	cr_expect_not_null(strstr(buffer, "exited"));
	cr_expect_not_null(strstr(buffer, "sleep 0.4 &"));
	cr_expect_eq(job_control->current, 0);
	cr_expect_eq(job_control->previous, 0);
	cr_expect_null(job_control->job_list);
	close(fd);
	close(read_fd);
	remove(filename);
	free_job_control(job_control);
}

Test(check_jobs_unit, basic_two_child_changes)
{
	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
	t_shell		*shell = init_shell(false);
	cr_assert_not_null(shell);
	shell->job_control = job_control;
	char		*input2 = strdup("sleep 1 &");
	char		*input = strdup("sleep 0.4 &");
	char		*filename = "/tmp/check_jobs_unit_basic_two_child_changes";
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
	check_jobs(job_control);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_eq(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_eq(job_control->current, 1);
	cr_expect_eq(job_control->previous, 0);
	cr_expect_not_null(job_control->job_list);
	close(read_fd);
	close(fd);
	fd = redirect_std_out(filename);
	memset(buffer, 0, 1024);
	cr_assert_gt(fd, 0);
	handle_input(shell, &input2);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	close(read_fd);
	cr_expect_not_null(strstr(buffer, "[2] +"));
	close(fd);
	fd = redirect_std_out(filename);
	check_jobs(job_control);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_eq(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_eq(job_control->current, 2);
	cr_expect_eq(job_control->previous, 1);
	cr_expect_not_null(job_control->job_list);
	close(read_fd);
	close(fd);
	usleep(500000);
	fd = redirect_std_out(filename);
	cr_assert_gt(fd, 0);
	check_jobs(job_control);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_not_null(strstr(buffer, "[1] -"));
	cr_expect_not_null(strstr(buffer, "exited"));
	cr_expect_not_null(strstr(buffer, "sleep 0.4 &"));
	cr_expect_eq(job_control->current, 2);
	cr_expect_eq(job_control->previous, 0);
	cr_expect_not_null(job_control->job_list);
	close(fd);
	close(read_fd);
	fd = redirect_std_out(filename);
	usleep(600000);
	check_jobs(job_control);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_not_null(strstr(buffer, "[2] +"));
	cr_expect_not_null(strstr(buffer, "exited"));
	cr_expect_not_null(strstr(buffer, "sleep 1 &"));
	cr_expect_eq(job_control->current, 0);
	cr_expect_eq(job_control->previous, 0);
	cr_expect_null(job_control->job_list);
	close(fd);
	close(read_fd);
	remove(filename);
	free_job_control(job_control);
}

Test(check_jobs_unit, basic_two_child_changes_reverse)
{
	t_job_cont	*job_control = (t_job_cont *)ft_memalloc(sizeof(t_job_cont));
	t_shell		*shell = init_shell(false);
	cr_assert_not_null(shell);
	shell->job_control = job_control;
	char		*input2 = strdup("sleep 0.4 &");
	char		*input = strdup("sleep 1 &");
	char		*filename = "/tmp/check_jobs_unit_basic_two_child_changes_reverse";
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
	check_jobs(job_control);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_eq(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_eq(job_control->current, 1);
	cr_expect_eq(job_control->previous, 0);
	cr_expect_not_null(job_control->job_list);
	close(read_fd);
	close(fd);
	fd = redirect_std_out(filename);
	memset(buffer, 0, 1024);
	cr_assert_gt(fd, 0);
	handle_input(shell, &input2);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	close(read_fd);
	cr_expect_not_null(strstr(buffer, "[2] +"));
	close(fd);
	fd = redirect_std_out(filename);
	check_jobs(job_control);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_eq(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_eq(job_control->current, 2);
	cr_expect_eq(job_control->previous, 1);
	cr_expect_not_null(job_control->job_list);
	close(read_fd);
	close(fd);
	usleep(500000);
	fd = redirect_std_out(filename);
	cr_assert_gt(fd, 0);
	check_jobs(job_control);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_not_null(strstr(buffer, "[2] +"));
	cr_expect_not_null(strstr(buffer, "exited"));
	cr_expect_not_null(strstr(buffer, "sleep 0.4 &"));
	cr_expect_eq(job_control->current, 1);
	cr_expect_eq(job_control->previous, 0);
	cr_expect_not_null(job_control->job_list);
	close(fd);
	close(read_fd);
	usleep(600000);
	fd = redirect_std_out(filename);
	check_jobs(job_control);
	memset(buffer, 0, 1024);
	read_fd = open(filename, O_RDONLY);
	cr_assert_gt(read_fd, 0);
	cr_expect_gt(read(read_fd, buffer, 1024), (ssize_t)0);
	cr_expect_not_null(strstr(buffer, "[1] +"));
	cr_expect_not_null(strstr(buffer, "exited"));
	cr_expect_not_null(strstr(buffer, "sleep 1 &"));
	cr_expect_eq(job_control->current, 0);
	cr_expect_eq(job_control->previous, 0);
	cr_expect_null(job_control->job_list);
	close(fd);
	close(read_fd);
	remove(filename);
	free_job_control(job_control);
}
