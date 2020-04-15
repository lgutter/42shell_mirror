/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_str.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: Invalid date        by               #+#    #+#                 */
/*   Updated: 0003/01/01 00:00:00 by               ########   odam.nl         */
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
	[parsing_error] = "Parsing error detected",
	[read_error] = "Error while read() call",
	[env_write_error] = "Environment key exists and overwrite is off",
	[env_not_found] = "Environment key not found",
	[env_empty_error] = "Environment is empty"
};
#endif
