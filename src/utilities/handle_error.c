/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 10:43:04 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/15 10:43:04 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "handle_error.h"

int		handle_error(int error_code)
{
	return (d_handle_error(STDERR_FILENO, error_code));
}

int		handle_error_str(int error_code, const char *str)
{
	return (d_handle_error_str(STDERR_FILENO, error_code, str));
}

int		handle_error_int(int error_code, int number)
{
	return (d_handle_error_int(STDERR_FILENO, error_code, number));
}

void	*handle_error_str_p(int error_code, const char *str, void *pointer)
{
	return (d_handle_error_str_p(STDERR_FILENO, error_code, str, pointer));
}

void	*handle_error_p(int error_code, void *pointer)
{
	return (d_handle_error_p(STDERR_FILENO, error_code, pointer));
}
