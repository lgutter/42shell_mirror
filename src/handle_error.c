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

#include "handle_error.h"
#include "error_str.h"

int		handle_error(int error_code)
{
	g_error_internal = error_code;
	ft_dprintf(STDERR_FILENO, "%s\n", g_error_str[error_code]);
	return (error_code);
}

int		handle_error_str(int error_code, const char *str)
{
	g_error_internal = error_code;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", g_error_str[error_code], str);
	return (error_code);
}

void	*handle_error_str_p(int error_code, const char *str, void *pointer)
{
	g_error_internal = error_code;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", g_error_str[error_code], str);
	return (pointer);
}

void	*handle_error_p(int error_code, void *pointer)
{
	g_error_internal = error_code;
	ft_dprintf(STDERR_FILENO, "%s\n", g_error_str[error_code]);
	return (pointer);
}
