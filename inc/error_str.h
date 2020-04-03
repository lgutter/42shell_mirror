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

#ifndef ERROR_STR_H
# define ERROR_STR_H
# include "handle_error.h"

/*
**	an array of all the error strings, using the error enums as index.
**	these strings will be used to print a relevant error message.
*/
static const char	*g_error_str[error_count] = {
	[no_error] = "Error code indicates no error",
	[malloc_error] = "Malloc failed to allocate memory",
	[invalid_token] = "Token is invalid",
	[parsing_error] = "Parsing error detected"
};
#endif
