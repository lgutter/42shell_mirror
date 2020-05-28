/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_snprintf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/11 13:40:08 by lgutter       #+#    #+#                 */
/*   Updated: 2019/12/13 11:19:06 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_string_n_info	init_sninfo(char *target, size_t len)
{
	t_string_n_info	sninfo;
	static size_t	index = 0;

	sninfo.target = target;
	sninfo.len = len;
	sninfo.index = &index;
	return (sninfo);
}

int						ft_snprintf(char *target, size_t len,
											const char *restrict format, ...)
{
	int				i;
	t_info			info;
	t_string_n_info	sninfo;

	sninfo = init_sninfo(target, len);
	info.target = &sninfo;
	info.writer = &ft_writer_string_n;
	info.totallen = 0;
	va_start(info.arguments, format);
	i = 0;
	while (format[i] != '\0' && *(sninfo.index) < sninfo.len)
	{
		if (format[i] == '%')
		{
			i += ft_process_conversion(&format[i], &info);
		}
		else
		{
			ft_writer_string_n(info.target, &info.totallen, &format[i], 1);
			i++;
		}
	}
	*(sninfo.index) = 0;
	va_end(info.arguments);
	return (info.totallen);
}
