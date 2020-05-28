/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dprintf.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/11 13:40:08 by lgutter       #+#    #+#                 */
/*   Updated: 2019/12/13 11:19:06 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_dprintf(int fd, const char *restrict format, ...)
{
	int			i;
	t_info		info;

	info.target = &fd;
	info.writer = &ft_writer_fd;
	info.totallen = 0;
	va_start(info.arguments, format);
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i += ft_process_conversion(&format[i], &info);
		}
		else
		{
			ft_writer_fd(info.target, &info.totallen, &format[i], 1);
			i++;
		}
	}
	va_end(info.arguments);
	return (info.totallen);
}
