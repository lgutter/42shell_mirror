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

struct s_err_params {
    int err_code;
};

ParameterizedTestParameters(handle_error_tests, param_test_all_error_codes) {
    static struct s_err_params err_params[] = {
		{0},
		{1},
		{2},
    };

    size_t nb_params = sizeof (err_params) / sizeof (struct s_err_params);
    return cr_make_param_array(struct s_err_params, err_params, nb_params);
}

ParameterizedTest(struct s_err_params *err_param, handle_error_tests, param_test_all_error_codes) {
	char *temp = NULL;

	cr_redirect_stderr();
	handle_error(err_param->err_code);
	ft_asprintf(&temp, "%s\n", g_error_str[err_param->err_code]);
	cr_assert_neq(temp, NULL);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
	free(temp);
	temp = NULL;
}

struct s_err_str_params {
    int err_code;
	const char err_str[1024];
};

ParameterizedTestParameters(handle_error_str_tests, param_test_all_error_codes_with_str) {
    static struct s_err_str_params err_str_params[] = {
		{0, "foo"},
		{1, "foo435ydfg"},
		{2, "foobarb"}
    };

    size_t nb_params = sizeof (err_str_params) / sizeof (struct s_err_str_params);
    return cr_make_param_array(struct s_err_str_params, err_str_params, nb_params);
}

ParameterizedTest(struct s_err_str_params *err_str_param, handle_error_str_tests, param_test_all_error_codes_with_str) {
	char *temp = NULL;

	cr_redirect_stderr();
	handle_error_str(err_str_param->err_code, err_str_param->err_str);
	ft_asprintf(&temp, "%s: %s\n", g_error_str[err_str_param->err_code], err_str_param->err_str);
	cr_assert_neq(temp, NULL);
	fflush(stderr);
	cr_expect_stderr_eq_str(temp);
	free(temp);
	temp = NULL;
}
