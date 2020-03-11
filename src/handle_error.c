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

int		handle_error(int error_code)
{
	ft_dprintf(2, "%s\n", g_error_str[error_code]);
	return (error_code);
}

int		handle_error_str(int error_code, const char *str)
{
	ft_dprintf(2, "%s: %s\n", g_error_str[error_code], str);
	return (error_code);
}
