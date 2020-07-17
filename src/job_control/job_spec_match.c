/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   job_spec_match.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/17 11:42:21 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/17 11:42:21 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

static size_t	get_job_spec_id(t_job_cont *job_control, const char *job_spec)
{
	size_t id;

	id = 0;
	if (job_spec[1] == '%' || job_spec[1] == '+')
		id = job_control->current;
	else if (job_spec[1] == '-')
		id = job_control->previous;
	else if (ft_isdigit(job_spec[1]) == 1)
		id = (size_t)ft_atoi(&(job_spec[1]));
	return (id);
}

bool			job_spec_match(t_job_cont *job_control,
											t_job *job, const char *job_spec)
{
	size_t		id;
	const char	*string;

	if (job_control == NULL || job == NULL ||
		job_spec == NULL || job_spec[0] != '%')
		return (false);
	id = get_job_spec_id(job_control, job_spec);
	if (job->id == id)
		return (true);
	if (job->command == NULL)
		return (false);
	if (job_spec[1] == '?')
	{
		string = &(job_spec[2]);
		if (ft_strstr(job->command, string) != NULL)
			return (true);
	}
	string = &(job_spec[1]);
	if (ft_strstr(job->command, string) == job->command)
		return (true);
	return (false);
}
