/* ************************************************************************** */
/*                                                                            */
/*   cetushell - 21 Shell                                 ::::::::            */
/*                                                      :+:    :+:            */
/*   By: dkroeke <dkroeke@student.codam.nl>            +:+                    */
/*       lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*                                                 #+#    #+#                 */
/*   License: GPLv3                                ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include <criterion/parameterized.h>
#include "handle_error.h"

static void redirect_std_err()
{
	cr_redirect_stderr();
}

ParameterizedTestParameters(handle_error_tests, param_test_all_error_codes)
{
    static int err_params[] = {
		0,
		1,
    };

    size_t nb_params = sizeof (err_params) / sizeof (int);
    return cr_make_param_array(int, err_params, nb_params);
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

struct s_err_str_params {
    int err_code;
	char err_str[64];
};

ParameterizedTestParameters(handle_error_str_tests, param_test_all_error_codes_with_str)
{
    static struct s_err_str_params err_str_params[] = {
		{0, "foo"},
		{1, "foo bar"},
    };

    size_t nb_params = sizeof (err_str_params) / sizeof (struct s_err_str_params);
    return cr_make_param_array(struct s_err_str_params, err_str_params, nb_params);
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
