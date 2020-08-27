/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_writer_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 17:03:28 by lgutter       #+#    #+#                 */
/*   Updated: 2019/11/25 16:17:51 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_writer_fd(void *target, unsigned long long *totallen,\
					const char *string, size_t len)
{
	int fd;

	fd = *((int *)target);
	if (len <= 0)
	{
		len = ft_strlen(string);
	}
	write(fd, string, len);
	*totallen += len;
}
