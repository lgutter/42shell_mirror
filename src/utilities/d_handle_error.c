/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   d_handle_error.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 10:43:04 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/07 22:07:57 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "handle_error.h"
#include "error_str.h"

int		d_handle_error(int fd, int error_code)
{
	if (error_code > 0 && error_code < error_count)
	{
		g_error_internal = error_code;
		ft_dprintf(fd, "Cetushell: %s\n", g_error_str[error_code]);
	}
	return (error_code);
}

int		d_handle_error_str(int fd, int error_code, const char *str)
{
	if (error_code > 0 && error_code < error_count)
	{
		g_error_internal = error_code;
		ft_dprintf(fd, "Cetushell: %s: %s\n", g_error_str[error_code], str);
	}
	return (error_code);
}

int		d_handle_error_int(int fd, int error_code, int number)
{
	if (error_code > 0 && error_code < error_count)
	{
		g_error_internal = error_code;
		ft_dprintf(fd, "Cetushell: %s: %i\n", g_error_str[error_code], number);
	}
	return (error_code);
}

void	*d_handle_error_str_p(int fd, int error_code,
								const char *str, void *pointer)
{
	if (error_code > 0 && error_code < error_count)
	{
		g_error_internal = error_code;
		ft_dprintf(fd, "Cetushell: %s: %s\n", g_error_str[error_code], str);
	}
	return (pointer);
}

void	*d_handle_error_p(int fd, int error_code, void *pointer)
{
	if (error_code > 0 && error_code < error_count)
	{
		g_error_internal = error_code;
		ft_dprintf(fd, "Cetushell: %s\n", g_error_str[error_code]);
	}
	return (pointer);
}
