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

#ifndef HANDLE_ERROR_H
# define HANDLE_ERROR_H
# include "ft_printf.h"

/*
**	enumerations used to pass error codes between functions.
*/
typedef enum		e_error
{
	unknown_error = 0,
	malloc_error,
	foo_error,
	error_count
}					t_error;

/*
**	an array of all the error strings, using the error enums as index.
**	these strings will be used to print a relevant error message.
*/
static const char	*g_error_str[error_count] = {
	[unknown_error] = "An unknown error occurred",
	[malloc_error] = "Malloc failed to allocate memory",
	[foo_error] = "foo fake error"
};

/*
**	handle_error takes an error_code (see error enums), and prints the relevant
**	error message, after which it returns the error code again.
**	arg: error_code: the error code as can be found in the error enumerations.
**	returns: the error code given as argument.
*/
int		handle_error(int error_code);

/*
**	handle_error_str takes an error_code (see error enums) and string as args,
**	and prints the relevant error message followed by the string,
**	after which it returns the error code again.
**	arg: error_code: the error code as can be found in the error enumerations.
**	arg: str: the string to be printed after the error message.
**	returns: the error code given as argument.
*/
int		handle_error_str(int error_code, const char *str);

#endif
