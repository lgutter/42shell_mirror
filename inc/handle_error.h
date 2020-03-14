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
# include <unistd.h>
# include "ft_printf.h"

/*
**	global variable used to store the most recent internal error code.
**	this can be used to check an error state. After the error state is
**	handled, it should be set back to 0.
*/
int					g_error_internal;

/*
**	enumerations used to indentify error codes easier.
*/
typedef enum		e_error
{
	no_error,
	malloc_error,
	error_count
}					t_error;

/*
**	handle_error takes an error_code (see error enums), and prints the
**	relevant error message, after which it returns the error code again.
**
**	arg: error_code: the error code as can be found in the error enumerations.
**	returns: the error code given as argument.
*/
int		handle_error(int error_code);

/*
**	handle_error_str takes an error_code (see error enums) and string
**	as args, and prints the relevant error message followed by the
**	string, after which it returns the error code again.
**
**	arg: error_code: the error code as can be found in the error enumerations.
**	arg: str: the string to be printed after the error message.
**	returns: the error code given as argument.
*/
int		handle_error_str(int error_code, const char *str);

/*
**	handle_error_str_p takes an error_code (see error enums), a string,
**	and a pointer as args, and prints the relevant error message
**	followed by the string, after which it returns the pointer given
**	as argument. This function is useful to call in a return statement
**	when the function it is called from returns something different than an int.
**
**	arg: error_code: the error code as can be found in the error enumerations.
**	arg: str: the string to be printed after the error message.
**	returns: the error code given as argument.
*/
void	*handle_error_str_p(int error_code, const char *str, void *pointer);

/*
**	handle_error_p takes an error_code (see error enums) and a pointer
**	as args, and prints the relevant error message, after which it
**	returns the pointer given as argument. This function is useful to
**	call in a return statement when the function it is called from
**	returns something different than an int.
**
**	arg: error_code: the error code as can be found in the error enumerations.
**	arg: pointer: the pointer to be returned after the error message is printed.
**	returns: the error code given as argument.
*/
void	*handle_error_p(int error_code, void *pointer);

#endif
