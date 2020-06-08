/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_redirects.spec.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/07 14:00:07 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/07 14:00:07 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include "processing.h"
#include "error_str.h"

static void	redirect_std_err()
{
	cr_redirect_stderr();
}

Test(process_redirects_unit, valid_std_out_to_file_expand)
{
	int				exp_ret = 0;
	int				exp_fd = 1;
	char			*exp_str = "bar";
	t_io_file		io_file = {redirect_out, strdup("$foo")};
	t_io_redirect	redirect = {"1", -1, &io_file, NULL, NULL};
	t_env			env = {strdup("foo"), strdup(exp_str), ENV_VAR, NULL};
	t_shell			shell;

	ft_bzero(&shell, sizeof(t_shell));
	shell.env = &env;
	int ret = process_redirects(&shell, &redirect);
	cr_expect_eq(exp_ret, ret, "expected ret %i, got %i!", exp_ret, ret);
	cr_expect_eq(redirect.io_fd, exp_fd, "expected converted fd %i, but got %i!", exp_fd, redirect.io_fd);
	cr_expect_not_null(io_file.filename);
	cr_expect_str_eq(io_file.filename, exp_str, "expected filename to be expanded to |%s|, but value is |%s|!", exp_str, io_file.filename);
}

Test(process_redirects_unit, valid_std_err_to_file_quotes)
{
	int				exp_ret = 0;
	int				exp_fd = 2;
	char			*exp_str = "$foo";
	t_io_file		io_file = {redirect_out, strdup("\'$foo\'")};
	t_io_redirect	redirect = {"2", -1, &io_file, NULL, NULL};
	t_env			env = {strdup("foo"), strdup("bar"), ENV_VAR, NULL};
	t_shell			shell;

	ft_bzero(&shell, sizeof(t_shell));
	shell.env = &env;
	int ret = process_redirects(&shell, &redirect);
	cr_expect_eq(exp_ret, ret, "expected ret %i, got %i!", exp_ret, ret);
	cr_expect_eq(redirect.io_fd, exp_fd, "expected converted fd %i, but got %i!", exp_fd, redirect.io_fd);
	cr_expect_not_null(io_file.filename);
	cr_expect_str_eq(io_file.filename, exp_str, "expected filename to be expanded to |%s|, but value is |%s|!", exp_str, io_file.filename);
}

Test(process_redirects_unit, valid_std_err_to_fd_number)
{
	int				exp_ret = 0;
	int				exp_fd = 2;
	char			*exp_str = "42";
	t_io_file		io_file = {redirect_out, strdup("42")};
	t_io_redirect	redirect = {"2", -1, &io_file, NULL, NULL};

	int ret = process_redirects(NULL, &redirect);
	cr_expect_eq(exp_ret, ret, "expected ret %i, got %i!", exp_ret, ret);
	cr_expect_eq(redirect.io_fd, exp_fd, "expected converted fd %i, but got %i!", exp_fd, redirect.io_fd);
	cr_expect_not_null(io_file.filename);
	cr_expect_str_eq(io_file.filename, exp_str, "expected filename to be expanded to |%s|, but value is |%s|!", exp_str, io_file.filename);
}

Test(process_redirects_unit, valid_std_in_to_fd_number_expand)
{
	int				exp_ret = 0;
	int				exp_fd = 0;
	char			*exp_str = "42";
	t_io_file		io_file = {redirect_fd_in, strdup("$foo")};
	t_io_redirect	redirect = {"0", -1, &io_file, NULL, NULL};
	t_env			env = {strdup("foo"), strdup("42"), ENV_VAR, NULL};
	t_shell			shell;

	ft_bzero(&shell, sizeof(t_shell));
	shell.env = &env;
	int ret = process_redirects(&shell, &redirect);
	cr_expect_eq(exp_ret, ret, "expected ret %i, got %i!", exp_ret, ret);
	cr_expect_eq(redirect.io_fd, exp_fd, "expected converted fd %i, but got %i!", exp_fd, redirect.io_fd);
	cr_expect_not_null(io_file.filename);
	cr_expect_str_eq(io_file.filename, exp_str, "expected filename to be expanded to |%s|, but value is |%s|!", exp_str, io_file.filename);
}

Test(process_redirects_unit, invalid_std_err_to_fd_string, .init = redirect_std_err)
{
	int				exp_ret = -1;
	int				exp_fd = 2;
	t_io_file		io_file = {redirect_fd_out, strdup("foo")};
	t_io_redirect	redirect = {"2", -1, &io_file, NULL, NULL};

	int ret = process_redirects(NULL, &redirect);
	cr_expect_eq(exp_ret, ret, "expected ret %i, got %i!", exp_ret, ret);
	cr_expect_eq(redirect.io_fd, exp_fd, "expected converted fd %i, but got %i!", exp_fd, redirect.io_fd);
	cr_expect_not_null(io_file.filename);
	char buff[1024];
	fflush(stderr);
	sprintf(buff, "Cetushell: %s: %s\n", g_error_str[ambig_redirect], io_file.filename);
	cr_expect_stderr_eq_str(buff);
}

Test(process_redirects_unit, invalid_empty_redirect, .init = redirect_std_err)
{
	int				exp_ret = parsing_error;
	t_io_redirect	redirect = {NULL, -1, NULL, NULL, NULL};

	int ret = process_redirects(NULL, &redirect);
	cr_expect_eq(exp_ret, ret, "expected ret %i, got %i!", exp_ret, ret);
	char buff[1024];
	fflush(stderr);
	sprintf(buff, "Cetushell: %s: %s\n", g_error_str[exp_ret], "empty redirect");
	cr_expect_stderr_eq_str(buff);
}
