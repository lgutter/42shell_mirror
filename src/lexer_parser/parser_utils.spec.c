/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_io_file.spec.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/10 13:17:43 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/10 13:17:43 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <criterion/redirect.h>
#include <criterion/parameterized.h>
#include "tokenizer.h"
#include "parser.h"

struct s_is_op_params
{
	t_type	token_type;
	int		expected_result;
};

ParameterizedTestParameters(is_redirect_op_unit, check_all_tokens)
{
    static struct s_is_op_params is_op_params[] = {
	{undetermined, 0},
	{WORD, 0},
	{IO_NUMBER, 0},
	{NEWLINE, 0},
	{PIPE, 0},
	{SEMI, 0},
	{AMP, 0},
	{LESS, 1},
	{GREAT, 1},
	{DLESS, 0},
	{DGREAT, 1},
	{LESSAMP, 1},
	{GREATAMP, 1},
    };

    size_t nb_params = sizeof (is_op_params) / sizeof (struct s_is_op_params);
    return cr_make_param_array(struct s_is_op_params, is_op_params, nb_params);
}

ParameterizedTest(struct s_is_op_params *param, is_redirect_op_unit, check_all_tokens)
{
	int result;
	t_token *token = (t_token *)malloc(sizeof(t_token) * 1);

	token->type = param->token_type;
	result = is_redirect_op(token);
	cr_expect_eq(result, param->expected_result, "result: %i", result);
	free(token);
	token = NULL;
}

Test(is_redirect_op_unit, invalid_NULL_token)
{
	int result;

	result = is_redirect_op(NULL);
	cr_expect_eq(result, 0, "result: %i", result);
}

ParameterizedTestParameters(is_seperator_op_unit, check_all_tokens)
{
    static struct s_is_op_params is_op_params[] = {
	{undetermined, 0},
	{WORD, 0},
	{IO_NUMBER, 0},
	{NEWLINE, 1},
	{PIPE, 0},
	{SEMI, 1},
	{AMP, 1},
	{LESS, 0},
	{GREAT, 0},
	{DLESS, 0},
	{DGREAT, 0},
	{LESSAMP, 0},
	{GREATAMP, 0},
    };

    size_t nb_params = sizeof (is_op_params) / sizeof (struct s_is_op_params);
    return cr_make_param_array(struct s_is_op_params, is_op_params, nb_params);
}

ParameterizedTest(struct s_is_op_params *param, is_seperator_op_unit, check_all_tokens)
{
	int result;
	t_token *token = (t_token *)malloc(sizeof(t_token) * 1);

	token->type = param->token_type;
	result = is_seperator_op(token);
	cr_expect_eq(result, param->expected_result, "result: %i", result);
	free(token);
	token = NULL;
}

Test(is_seperator_op_unit, invalid_NULL_token)
{
	int result;

	result = is_seperator_op(NULL);
	cr_expect_eq(result, 0, "result: %i", result);
}

ParameterizedTestParameters(is_start_of_redirect_unit, check_all_tokens)
{
    static struct s_is_op_params is_op_params[] = {
	{undetermined, 0},
	{WORD, 0},
	{IO_NUMBER, 1},
	{NEWLINE, 0},
	{PIPE, 0},
	{SEMI, 0},
	{AMP, 0},
	{LESS, 1},
	{GREAT, 1},
	{DLESS, 1},
	{DGREAT, 1},
	{LESSAMP, 1},
	{GREATAMP, 1},
    };

    size_t nb_params = sizeof (is_op_params) / sizeof (struct s_is_op_params);
    return cr_make_param_array(struct s_is_op_params, is_op_params, nb_params);
}

ParameterizedTest(struct s_is_op_params *param, is_start_of_redirect_unit, check_all_tokens)
{
	int result;
	t_token *token = (t_token *)malloc(sizeof(t_token) * 1);

	token->type = param->token_type;
	result = is_start_of_redirect(token);
	cr_expect_eq(result, param->expected_result, "result: %i", result);
	free(token);
	token = NULL;
}

Test(is_start_of_redirect_unit, invalid_NULL_token)
{
	int result;

	result = is_start_of_redirect(NULL);
	cr_expect_eq(result, 0, "result: %i", result);
}
