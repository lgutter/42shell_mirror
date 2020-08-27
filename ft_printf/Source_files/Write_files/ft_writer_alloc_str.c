/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_writer_alloc_str.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/28 11:19:04 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/28 11:19:04 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_writer_alloc_str(void *target, unsigned long long *totallen,\
					const char *string, size_t len)
{
	t_alloc_str_info	*info;
	size_t				real_len;

	info = (t_alloc_str_info *)target;
	real_len = ft_strlen(string);
	if (len <= 0 || len > real_len)
		len = real_len;
	if (len < (AS_BUFF_LEN - info->len))
	{
		ft_strncpy(&(info->buffer[info->len]), string, len);
		info->len += len;
	}
	else
	{
		ft_strexpand(info->target, info->buffer);
		ft_strexpand(info->target, string);
		ft_bzero(info->buffer, AS_BUFF_LEN);
		info->len = 0;
	}
	*totallen += len;
}
