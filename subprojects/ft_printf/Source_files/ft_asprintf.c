/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_asprintf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/11 13:40:08 by lgutter       #+#    #+#                 */
/*   Updated: 2019/12/13 11:19:06 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_alloc_str_info	init_asinfo(char **target)
{
	t_alloc_str_info	asinfo;

	asinfo.target = target;
	ft_bzero(asinfo.buffer, AS_BUFF_LEN);
	asinfo.len = 0;
	return (asinfo);
}

int						ft_asprintf(char **target,
								const char *restrict format, ...)
{
	int					i;
	t_info				info;
	t_alloc_str_info	asinfo;

	asinfo = init_asinfo(target);
	info.target = &asinfo;
	info.writer = &ft_writer_alloc_str;
	info.totallen = 0;
	va_start(info.arguments, format);
	i = 0;
	*target = NULL;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			i += ft_process_conversion(&format[i], &info);
		else
		{
			ft_writer_alloc_str(info.target, &info.totallen, &format[i], 1);
			i++;
		}
	}
	if (asinfo.len > 0)
		ft_strexpand(target, asinfo.buffer);
	va_end(info.arguments);
	return (info.totallen);
}
