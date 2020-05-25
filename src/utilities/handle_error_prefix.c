/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_error_prefix.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 10:43:04 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/07 22:22:43 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "handle_error.h"
#include "error_str.h"

int		handle_prefix_error(int error_code, char *prefix)
{
	g_error_internal = error_code;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", prefix, g_error_str[error_code]);
	return (error_code);
}

int		handle_prefix_error_str(int error_code, char *prefix, char *str)
{
	g_error_internal = error_code;
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", prefix, str,
		g_error_str[error_code]);
	return (error_code);
}