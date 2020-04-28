/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   d_handle_error.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 10:43:04 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/15 10:43:04 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "handle_error.h"
#include "error_str.h"

int		d_handle_error(int fd, int error_code)
{
	g_error_internal = error_code;
	ft_dprintf(fd, "%s\n", g_error_str[error_code]);
	return (error_code);
}

int		d_handle_error_str(int fd, int error_code, const char *str)
{
	g_error_internal = error_code;
	ft_dprintf(fd, "%s: %s\n", g_error_str[error_code], str);
	return (error_code);
}

int		d_handle_error_int(int fd, int error_code, int number)
{
	g_error_internal = error_code;
	ft_dprintf(fd, "%s: %i\n", g_error_str[error_code], number);
	return (error_code);
}

void	*d_handle_error_str_p(int fd, int error_code,
								const char *str, void *pointer)
{
	g_error_internal = error_code;
	ft_dprintf(fd, "%s: %s\n", g_error_str[error_code], str);
	return (pointer);
}

void	*d_handle_error_p(int fd, int error_code, void *pointer)
{
	g_error_internal = error_code;
	ft_dprintf(fd, "%s\n", g_error_str[error_code]);
	return (pointer);
}
