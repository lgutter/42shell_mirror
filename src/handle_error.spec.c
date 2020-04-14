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

static void redirect_std_err()
{
	cr_redirect_stderr();
}

struct s_err_str_params
{
	int err_code;
	char err_str[64];
};

struct s_err_str_p_params
{
	int err_code;
	char err_str[64];
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
		0,
		1,
		2,
		3,
		4,
    };

    size_t nb_params = sizeof (err_params) / sizeof (int);
    return cr_make_param_array(int, err_params, nb_params);
}

ParameterizedTestParameters(handle_error_str_tests, param_test_all_error_codes_with_str)
{
    static struct s_err_str_params err_str_params[] = {
		{0, "foo"},
		{1, "foo bar"},
		{2, "foo"},
		{3, "bar"},
		{4, "baz"}
    };

    size_t nb_params = sizeof (err_str_params) / sizeof (struct s_err_str_params);
    return cr_make_param_array(struct s_err_str_params, err_str_params, nb_params);
}

ParameterizedTestParameters(handle_error_p_tests, param_test_all_error_codes_with_p)
{
    static struct s_err_p_params err_p_params[] = {
		{0, (void *)21},
		{1, (void *)42},
		{2, (void *)12},
		{3, (void *)26},
		{4, (void *)420},
    };

    size_t nb_params = sizeof (err_p_params) / sizeof (struct s_err_p_params);
    return cr_make_param_array(struct s_err_p_params, err_p_params, nb_params);
}

ParameterizedTestParameters(handle_error_str_p_tests, param_test_all_error_codes_with_str_p)
{
    static struct s_err_str_p_params err_str_params[] = {
		{0, "foo", (void *)21},
		{1, "foo bar", (void *)42},
		{2, "foo bar", (void *)26},
		{3, "foo bar", (void *)13},
		{4, "foo foo", (void *)457},
    };

    size_t nb_params = sizeof (err_str_params) / sizeof (struct s_err_str_p_params);
    return cr_make_param_array(struct s_err_str_p_params, err_str_params, nb_params);
}

ParameterizedTest(int *param, handle_error_tests, param_test_all_error_codes, .init= redirect_std_err)
{
	char *temp = NULL;

	handle_error(*param);
	ft_asprintf(&temp, "%s\n", g_error_str[*param]);
	cr_assert_neq(temp, NULL);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
	free(temp);
	temp = NULL;
}

ParameterizedTest(struct s_err_str_params *param, handle_error_str_tests, param_test_all_error_codes_with_str, .init= redirect_std_err)
{
	char *temp = NULL;

	cr_redirect_stderr();
	handle_error_str(param->err_code, param->err_str);
	ft_asprintf(&temp, "%s: %s\n", g_error_str[param->err_code], param->err_str);
	cr_assert_neq(temp, NULL);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
	free(temp);
	temp = NULL;
}

ParameterizedTest(struct s_err_str_p_params *param, handle_error_str_p_tests, param_test_all_error_codes_with_str_p, .init= redirect_std_err)
{
	char	*temp = NULL;
	void	*ret = NULL;

	cr_redirect_stderr();
	ret = handle_error_str_p(param->err_code, param->err_str, param->pointer);
	ft_asprintf(&temp, "%s: %s\n", g_error_str[param->err_code], param->err_str);
	cr_assert_neq(temp, NULL);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
	cr_expect_eq(ret, param->pointer);
	free(temp);
	temp = NULL;
}

ParameterizedTest(struct s_err_p_params *param, handle_error_p_tests, param_test_all_error_codes_with_p, .init= redirect_std_err)
{
	char	*temp = NULL;
	void	*ret = NULL;

	cr_redirect_stderr();
	ret = handle_error_p(param->err_code, param->pointer);
	ft_asprintf(&temp, "%s\n", g_error_str[param->err_code]);
	cr_assert_neq(temp, NULL);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
	cr_expect_eq(ret, param->pointer);
	free(temp);
	temp = NULL;
}
