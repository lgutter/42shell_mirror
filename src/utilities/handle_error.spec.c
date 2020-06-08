/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_error.spec.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: Invalid date        by               #+#    #+#                 */
/*   Updated: 0003/01/01 00:00:00 by               ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include <criterion/parameterized.h>
#include "handle_error.h"
#include "error_str.h"
#include <stdio.h>

static void redirect_std_err()
{
	cr_redirect_stderr();
}

struct s_err_str_params
{
	int err_code;
	char err_str[128];
};

struct s_err_str_p_params
{
	int err_code;
	char err_str[128];
	void *pointer;
};

struct s_err_p_params
{
	int err_code;
	void *pointer;
};

ParameterizedTestParameters(handle_error_tests, param_test_all_error_codes)
{
    static int err_params[] = {
	no_error,
	malloc_error,
	invalid_token,
	parsing_error,
	read_error,
	env_write_error,
	env_not_found,
	env_empty_error,
	histfile_format_error,
	error_histpath,
	no_read_permission_hist,
	no_write_permission_hist,
	history_filesize_error,
	no_such_file_or_dir,
	cmd_not_found,
	pipe_failure,
	fork_failure,
	execve_failure,
	access_denied,
	bad_fd_error,
	is_dir_error,
	ambig_redirect,
	error_ronly,
	error_inv_format,
	too_many_arguments,
	too_few_arguments,
	invalid_option,
	var_not_set,
	restore_fd_fail,
	dup2_fd_fail,
	exit_shell_code,
	not_a_dir_error
    };

    size_t nb_params = sizeof (err_params) / sizeof (int);
    return cr_make_param_array(int, err_params, nb_params);
}

ParameterizedTestParameters(handle_error_str_tests, param_test_all_error_codes_with_str)
{
    static struct s_err_str_params err_str_params[] = {
		{no_error, "foo bar"},
		{malloc_error, "foo bar"},
		{invalid_token, "foo bar"},
		{parsing_error, "foo bar"},
		{read_error, "foo bar"},
		{env_write_error, "foo bar"},
		{env_not_found, "foo bar"},
		{env_empty_error, "foo bar"},
		{histfile_format_error, "foo bar"},
		{error_histpath, "foo bar"},
		{no_read_permission_hist, "foo bar"},
		{no_write_permission_hist, "foo bar"},
		{history_filesize_error, "foo bar"},
		{no_such_file_or_dir, "foo bar"},
		{cmd_not_found, "foo bar"},
		{pipe_failure, "foo bar"},
		{fork_failure, "foo bar"},
		{execve_failure, "foo bar"},
		{access_denied, "foo bar"},
		{bad_fd_error, "foo bar"},
		{is_dir_error, "foo bar"},
		{ambig_redirect, "foo bar"},
		{error_ronly, "foo bar"},
		{error_inv_format, "foo bar"},
		{too_many_arguments, "foo bar"},
		{too_few_arguments, "foo bar"},
		{invalid_option, "foo bar"},
		{var_not_set, "foo bar"},
		{restore_fd_fail, "foo bar"},
		{dup2_fd_fail, "foo bar"},
		{exit_shell_code, "foo bar"},
		{not_a_dir_error, "foo bar"},
    };

    size_t nb_params = sizeof (err_str_params) / sizeof (struct s_err_str_params);
    return cr_make_param_array(struct s_err_str_params, err_str_params, nb_params);
}

ParameterizedTestParameters(handle_error_p_tests, param_test_all_error_codes_with_p)
{
    static struct s_err_p_params err_p_params[] = {
		{no_error, (void *)42},
		{malloc_error, (void *)42},
		{invalid_token, (void *)42},
		{parsing_error, (void *)42},
		{read_error, (void *)42},
		{env_write_error, (void *)42},
		{env_not_found, (void *)42},
		{env_empty_error, (void *)42},
		{histfile_format_error, (void *)42},
		{error_histpath, (void *)42},
		{no_read_permission_hist, (void *)42},
		{no_write_permission_hist, (void *)42},
		{history_filesize_error, (void *)42},
		{no_such_file_or_dir, (void *)42},
		{cmd_not_found, (void *)42},
		{pipe_failure, (void *)42},
		{fork_failure, (void *)42},
		{execve_failure, (void *)42},
		{access_denied, (void *)42},
		{bad_fd_error, (void *)42},
		{is_dir_error, (void *)42},
		{ambig_redirect, (void *)42},
		{error_ronly, (void *)42},
		{error_inv_format, (void *)42},
		{too_many_arguments, (void *)42},
		{too_few_arguments, (void *)42},
		{invalid_option, (void *)42},
		{var_not_set, (void *)42},
		{restore_fd_fail, (void *)42},
		{dup2_fd_fail, (void *)42},
		{exit_shell_code, (void *)42},
		{not_a_dir_error, (void *)42}
    };

    size_t nb_params = sizeof (err_p_params) / sizeof (struct s_err_p_params);
    return cr_make_param_array(struct s_err_p_params, err_p_params, nb_params);
}

ParameterizedTestParameters(handle_error_str_p_tests, param_test_all_error_codes_with_str_p)
{
    static struct s_err_str_p_params err_str_params[] = {
		{no_error, "foo", (void *)42},
		{malloc_error, "foo", (void *)42},
		{invalid_token, "foo", (void *)42},
		{parsing_error, "foo", (void *)42},
		{read_error, "foo", (void *)42},
		{env_write_error, "foo", (void *)42},
		{env_not_found, "foo", (void *)42},
		{env_empty_error, "foo", (void *)42},
		{histfile_format_error, "foo", (void *)42},
		{error_histpath, "foo", (void *)42},
		{no_read_permission_hist, "foo", (void *)42},
		{no_write_permission_hist, "foo", (void *)42},
		{history_filesize_error, "foo", (void *)42},
		{no_such_file_or_dir, "foo", (void *)42},
		{cmd_not_found, "foo", (void *)42},
		{pipe_failure, "foo", (void *)42},
		{fork_failure, "foo", (void *)42},
		{execve_failure, "foo", (void *)42},
		{access_denied, "foo", (void *)42},
		{bad_fd_error, "foo", (void *)42},
		{is_dir_error, "foo", (void *)42},
		{ambig_redirect, "foo", (void *)42},
		{error_ronly, "foo", (void *)42},
		{error_inv_format, "foo", (void *)42},
		{too_many_arguments, "foo", (void *)42},
		{too_few_arguments, "foo", (void *)42},
		{invalid_option, "foo", (void *)42},
		{var_not_set, "foo", (void *)42},
		{restore_fd_fail, "foo", (void *)42},
		{dup2_fd_fail, "foo", (void *)42},
		{exit_shell_code, "foo", (void *)42},
		{not_a_dir_error, "foo", (void *)42},
    };

    size_t nb_params = sizeof (err_str_params) / sizeof (struct s_err_str_p_params);
    return cr_make_param_array(struct s_err_str_p_params, err_str_params, nb_params);
}

ParameterizedTest(int *param, handle_error_tests, param_test_all_error_codes, .init= redirect_std_err)
{
	char	temp[1024];

	handle_error(*param);
	snprintf(temp, 1024, "Cetushell: %s\n", g_error_str[*param]);
	cr_assert_neq(temp, NULL);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
}

ParameterizedTest(struct s_err_str_params *param, handle_error_str_tests, param_test_all_error_codes_with_str, .init= redirect_std_err)
{
	char temp[1024];

	ft_bzero(temp, 1024);
	cr_redirect_stderr();
	handle_error_str(param->err_code, param->err_str);
	snprintf(temp, 1024, "Cetushell: %s: %s\n", g_error_str[param->err_code], param->err_str);
	cr_assert_neq(temp, NULL);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
}

ParameterizedTest(struct s_err_str_p_params *param, handle_error_str_p_tests, param_test_all_error_codes_with_str_p, .init= redirect_std_err)
{
	char temp[1024];
	void	*ret = NULL;

	ft_bzero(temp, 1024);
	cr_redirect_stderr();
	ret = handle_error_str_p(param->err_code, param->err_str, param->pointer);
	snprintf(temp, 1024, "Cetushell: %s: %s\n", g_error_str[param->err_code], param->err_str);
	cr_assert_neq(temp, NULL);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
	cr_expect_eq(ret, param->pointer);
}

ParameterizedTest(struct s_err_p_params *param, handle_error_p_tests, param_test_all_error_codes_with_p, .init= redirect_std_err)
{
	char temp[1024];
	void	*ret = NULL;

	ft_bzero(temp, 1024);
	cr_redirect_stderr();
	ret = handle_error_p(param->err_code, param->pointer);
	snprintf(temp, 1024, "Cetushell: %s\n", g_error_str[param->err_code]);
	cr_assert_neq(temp, NULL);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
	cr_expect_eq(ret, param->pointer);
}

Test(handle_error_str_tests, invalid_NULL_string, .init= redirect_std_err)
{
	char temp[1024];
	char *null = NULL;

	ft_bzero(temp, 1024);
	cr_redirect_stderr();
	handle_error_str(1, NULL);
	snprintf(temp, 1024, "Cetushell: %s: %s\n", g_error_str[1], null);
	cr_assert_neq(temp, NULL);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
}

Test(handle_error_str_p_tests, invalid_NULL_string, .init= redirect_std_err)
{
	char temp[1024];
	char *ret;
	char *null = NULL;

	ft_bzero(temp, 1024);
	cr_redirect_stderr();
	ret = handle_error_str_p(1, NULL, (void*)42);
	snprintf(temp, 1024, "Cetushell: %s: %s\n", g_error_str[1], null);
	cr_assert_neq(temp, NULL);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
	cr_expect_eq((void*)42, ret);
}
