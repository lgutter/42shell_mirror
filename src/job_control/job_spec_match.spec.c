/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   job_spec_match.spec.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/17 11:42:21 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/17 11:42:21 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "job_control.h"

// bool			job_spec_match(t_job_cont *job_control,
// 											t_job *job, const char *job_spec);

Test(job_spec_match_unit, basic_job_id)
{
	// SIMPLY FILL IN THESE VALUES:
	char*		command =	"sleep 5 &";
	const char*	job_spec =	"%1";
	bool	job_is_current = true;
	int		expected_ret =	true;



	// no need to modify this part.
	t_shell		*shell = init_shell(false);
	t_job_cont	job_control = {0, 0, NULL, true};
	shell->job_control = &job_control;
	t_job		*job = init_job(shell, command, (command[strlen(command) - 1]) == '&' ? false : true);
	if (job_is_current)
		job_control.current = 1;
	char		*boolstr[2] = { "false", "true"};
	bool		ret;

	ret = job_spec_match(shell->job_control, job, job_spec);
	cr_expect_eq(ret, expected_ret, "with command \"%s\" and job_spec [%s], expected %s but result was %s!", job->command, job_spec, boolstr[expected_ret], boolstr[ret]);
}

Test(job_spec_match_unit, basic_job_wrong_id)
{
	// SIMPLY FILL IN THESE VALUES:
	char*		command =	"sleep 5 &";
	const char*	job_spec =	"%2";
	bool	job_is_current = true;
	int		expected_ret =	false;



	// no need to modify this part.
	t_shell		*shell = init_shell(false);
	t_job_cont	job_control = {0, 0, NULL, true};
	shell->job_control = &job_control;
	t_job		*job = init_job(shell, command, (command[strlen(command) - 1]) == '&' ? false : true);
	if (job_is_current)
		job_control.current = 1;
	char		*boolstr[2] = { "false", "true"};
	bool		ret;

	ret = job_spec_match(shell->job_control, job, job_spec);
	cr_expect_eq(ret, expected_ret, "with command \"%s\" and job_spec [%s], expected %s but result was %s!", job->command, job_spec, boolstr[expected_ret], boolstr[ret]);
}

Test(job_spec_match_unit, basic_job_current)
{
	// SIMPLY FILL IN THESE VALUES:
	char*		command =	"sleep 5 &";
	const char*	job_spec =	"%+";
	bool	job_is_current = true;
	int		expected_ret =	true;



	// no need to modify this part.
	t_shell		*shell = init_shell(false);
	t_job_cont	job_control = {0, 0, NULL, true};
	shell->job_control = &job_control;
	t_job		*job = init_job(shell, command, (command[strlen(command) - 1]) == '&' ? false : true);
	if (job_is_current)
		job_control.current = 1;
	char		*boolstr[2] = { "false", "true"};
	bool		ret;

	ret = job_spec_match(shell->job_control, job, job_spec);
	cr_expect_eq(ret, expected_ret, "with command \"%s\" and job_spec [%s], expected %s but result was %s!", job->command, job_spec, boolstr[expected_ret], boolstr[ret]);
}

Test(job_spec_match_unit, basic_job_not_current)
{
	// SIMPLY FILL IN THESE VALUES:
	char*		command =	"sleep 5 &";
	const char*	job_spec =	"%+";
	bool	job_is_current = false;
	int		expected_ret =	false;



	// no need to modify this part.
	t_shell		*shell = init_shell(false);
	t_job_cont	job_control = {0, 0, NULL, true};
	shell->job_control = &job_control;
	t_job		*job = init_job(shell, command, (command[strlen(command) - 1]) == '&' ? false : true);
	if (job_is_current)
		job_control.current = 1;
	char		*boolstr[2] = { "false", "true"};
	bool		ret;

	ret = job_spec_match(shell->job_control, job, job_spec);
	cr_expect_eq(ret, expected_ret, "with command \"%s\" and job_spec [%s], expected %s but result was %s!", job->command, job_spec, boolstr[expected_ret], boolstr[ret]);
}

Test(job_spec_match_unit, basic_job_current_percent_sign)
{
	// SIMPLY FILL IN THESE VALUES:
	char*		command =	"sleep 5 &";
	const char*	job_spec =	"%%";
	bool	job_is_current = true;
	int		expected_ret =	true;



	// no need to modify this part.
	t_shell		*shell = init_shell(false);
	t_job_cont	job_control = {0, 0, NULL, true};
	shell->job_control = &job_control;
	t_job		*job = init_job(shell, command, (command[strlen(command) - 1]) == '&' ? false : true);
	if (job_is_current)
		job_control.current = 1;
	char		*boolstr[2] = { "false", "true"};
	bool		ret;

	ret = job_spec_match(shell->job_control, job, job_spec);
	cr_expect_eq(ret, expected_ret, "with command \"%s\" and job_spec [%s], expected %s but result was %s!", job->command, job_spec, boolstr[expected_ret], boolstr[ret]);
}

Test(job_spec_match_unit, basic_job_previous)
{
	// SIMPLY FILL IN THESE VALUES:
	char*		command =	"sleep 5 &";
	const char*	job_spec =	"%-";
	bool	job_is_current = true;
	int		expected_ret =	false;



	// no need to modify this part.
	t_shell		*shell = init_shell(false);
	t_job_cont	job_control = {0, 0, NULL, true};
	shell->job_control = &job_control;
	t_job		*job = init_job(shell, command, (command[strlen(command) - 1]) == '&' ? false : true);
	if (job_is_current)
		job_control.current = 1;
	char		*boolstr[2] = { "false", "true"};
	bool		ret;

	ret = job_spec_match(shell->job_control, job, job_spec);
	cr_expect_eq(ret, expected_ret, "with command \"%s\" and job_spec [%s], expected %s but result was %s!", job->command, job_spec, boolstr[expected_ret], boolstr[ret]);
}

Test(job_spec_match_unit, basic_job_begins_with)
{
	// SIMPLY FILL IN THESE VALUES TO MODIFY THE TEST:
	char*		command =	"sleep 5 &";
	const char*	job_spec =	"%sle";
	bool	job_is_current = true;
	int		expected_ret =	true;



	// no need to modify this part.
	t_shell		*shell = init_shell(false);
	t_job_cont	job_control = {0, 0, NULL, true};
	shell->job_control = &job_control;
	t_job		*job = init_job(shell, command, (command[strlen(command) - 1]) == '&' ? false : true);
	if (job_is_current)
		job_control.current = 1;
	char		*boolstr[2] = { "false", "true"};
	bool		ret;

	ret = job_spec_match(shell->job_control, job, job_spec);
	cr_expect_eq(ret, expected_ret, "with command \"%s\" and job_spec [%s], expected %s but result was %s!", job->command, job_spec, boolstr[expected_ret], boolstr[ret]);
}

Test(job_spec_match_unit, basic_job_does_not_begin_with)
{
	// SIMPLY FILL IN THESE VALUES TO MODIFY THE TEST:
	char*		command =	"sleep 5 &";
	const char*	job_spec =	"%foo";
	bool	job_is_current = true;
	int		expected_ret =	false;



	// no need to modify this part.
	t_shell		*shell = init_shell(false);
	t_job_cont	job_control = {0, 0, NULL, true};
	shell->job_control = &job_control;
	t_job		*job = init_job(shell, command, (command[strlen(command) - 1]) == '&' ? false : true);
	if (job_is_current)
		job_control.current = 1;
	char		*boolstr[2] = { "false", "true"};
	bool		ret;

	ret = job_spec_match(shell->job_control, job, job_spec);
	cr_expect_eq(ret, expected_ret, "with command \"%s\" and job_spec [%s], expected %s but result was %s!", job->command, job_spec, boolstr[expected_ret], boolstr[ret]);
}

Test(job_spec_match_unit, basic_job_contains_string)
{
	// SIMPLY FILL IN THESE VALUES TO MODIFY THE TEST:
	char*		command =	"sleep 5 &";
	const char*	job_spec =	"%?ep 5";
	bool	job_is_current = true;
	int		expected_ret =	true;



	// no need to modify this part.
	t_shell		*shell = init_shell(false);
	t_job_cont	job_control = {0, 0, NULL, true};
	shell->job_control = &job_control;
	t_job		*job = init_job(shell, command, (command[strlen(command) - 1]) == '&' ? false : true);
	if (job_is_current)
		job_control.current = 1;
	char		*boolstr[2] = { "false", "true"};
	bool		ret;

	ret = job_spec_match(shell->job_control, job, job_spec);
	cr_expect_eq(ret, expected_ret, "with command \"%s\" and job_spec [%s], expected %s but result was %s!", job->command, job_spec, boolstr[expected_ret], boolstr[ret]);
}

Test(job_spec_match_unit, basic_job_does_not_contain_string)
{
	// SIMPLY FILL IN THESE VALUES TO MODIFY THE TEST:
	char*		command =	"sleep 5 &";
	const char*	job_spec =	"%?bar";
	bool	job_is_current = true;
	int		expected_ret =	false;



	// no need to modify this part.
	t_shell		*shell = init_shell(false);
	t_job_cont	job_control = {0, 0, NULL, true};
	shell->job_control = &job_control;
	t_job		*job = init_job(shell, command, (command[strlen(command) - 1]) == '&' ? false : true);
	if (job_is_current)
		job_control.current = 1;
	char		*boolstr[2] = { "false", "true"};
	bool		ret;

	ret = job_spec_match(shell->job_control, job, job_spec);
	cr_expect_eq(ret, expected_ret, "with command \"%s\" and job_spec [%s], expected %s but result was %s!", job->command, job_spec, boolstr[expected_ret], boolstr[ret]);
}

Test(job_spec_match_unit, error_job_command_is_null)
{
	// SIMPLY FILL IN THESE VALUES TO MODIFY THE TEST:
	char*		command =	NULL;
	const char*	job_spec =	"%foo";
	bool	job_is_current = true;
	int		expected_ret =	false;



	// no need to modify this part.
	t_shell		*shell = init_shell(false);
	t_job_cont	job_control = {0, 0, NULL, true};
	shell->job_control = &job_control;
	t_job		*job = init_job(shell, command, false);
	if (job_is_current)
		job_control.current = 1;
	char		*boolstr[2] = { "false", "true"};
	bool		ret;

	ret = job_spec_match(shell->job_control, job, job_spec);
	cr_expect_eq(ret, expected_ret, "with command \"%s\" and job_spec [%s], expected %s but result was %s!", job->command, job_spec, boolstr[expected_ret], boolstr[ret]);
}

Test(job_spec_match_unit, error_invalid_job_spec)
{
	// SIMPLY FILL IN THESE VALUES TO MODIFY THE TEST:
	char*		command =	"sleep 5&";
	const char*	job_spec =	"foo";
	bool	job_is_current = true;
	int		expected_ret =	false;



	// no need to modify this part.
	t_shell		*shell = init_shell(false);
	t_job_cont	job_control = {0, 0, NULL, true};
	shell->job_control = &job_control;
	t_job		*job = init_job(shell, command, (command[strlen(command) - 1]) == '&' ? false : true);
	if (job_is_current)
		job_control.current = 1;
	char		*boolstr[2] = { "false", "true"};
	bool		ret;

	ret = job_spec_match(shell->job_control, job, job_spec);
	cr_expect_eq(ret, expected_ret, "with command \"%s\" and job_spec [%s], expected %s but result was %s!", job->command, job_spec, boolstr[expected_ret], boolstr[ret]);
}

Test(job_spec_match_unit, error_null_job_spec)
{
	// SIMPLY FILL IN THESE VALUES TO MODIFY THE TEST:
	char*		command =	"sleep 5&";
	const char*	job_spec =	NULL;
	bool	job_is_current = true;
	int		expected_ret =	false;



	// no need to modify this part.
	t_shell		*shell = init_shell(false);
	t_job_cont	job_control = {0, 0, NULL, true};
	shell->job_control = &job_control;
	t_job		*job = init_job(shell, command, (command[strlen(command) - 1]) == '&' ? false : true);
	if (job_is_current)
		job_control.current = 1;
	char		*boolstr[2] = { "false", "true"};
	bool		ret;

	ret = job_spec_match(shell->job_control, job, job_spec);
	cr_expect_eq(ret, expected_ret, "with command \"%s\" and job_spec [%s], expected %s but result was %s!", job->command, job_spec, boolstr[expected_ret], boolstr[ret]);
}

Test(job_spec_match_unit, error_null_job)
{
	// SIMPLY FILL IN THESE VALUES TO MODIFY THE TEST:
	// char*		command =	"sleep 5&";
	const char*	job_spec =	"%1";
	bool	job_is_current = true;
	int		expected_ret =	false;



	// no need to modify this part.
	t_shell		*shell = init_shell(false);
	t_job_cont	job_control = {0, 0, NULL, true};
	shell->job_control = &job_control;
	t_job		*job = NULL;
	if (job_is_current)
		job_control.current = 1;
	char		*boolstr[2] = { "false", "true"};
	bool		ret;

	ret = job_spec_match(shell->job_control, job, job_spec);
	cr_expect_eq(ret, expected_ret, "with command \"%s\" and job_spec [%s], expected %s but result was %s!", job->command, job_spec, boolstr[expected_ret], boolstr[ret]);
}

Test(job_spec_match_unit, error_null_job_control)
{
	// SIMPLY FILL IN THESE VALUES TO MODIFY THE TEST:
	char*		command =	"sleep 5&";
	const char*	job_spec =	"%1";
	// bool	job_is_current = true;
	int		expected_ret =	false;



	// no need to modify this part.
	t_shell		*shell = init_shell(false);
	// t_job_cont	job_control = {0, 0, NULL, true};
	shell->job_control = NULL;
	t_job		*job = init_job(shell, command, (command[strlen(command) - 1]) == '&' ? false : true);
	// if (job_is_current)
	// 	job_control.current = 1;
	char		*boolstr[2] = { "false", "true"};
	bool		ret;

	ret = job_spec_match(shell->job_control, job, job_spec);
	cr_expect_eq(ret, expected_ret, "with command \"%s\" and job_spec [%s], expected %s but result was %s!", job->command, job_spec, boolstr[expected_ret], boolstr[ret]);
}
