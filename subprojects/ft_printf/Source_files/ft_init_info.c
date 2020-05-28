/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_init_info.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 14:50:09 by lgutter       #+#    #+#                 */
/*   Updated: 2019/11/19 16:19:42 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_init_info(const char *format, t_info *info)
{
	int i;

	i = 1;
	info->flags = 0;
	info->width = 0;
	info->precision = 0;
	info->lenmod = 0;
	info->precfound = -1;
	i = ft_find_flags(format, info, i);
	i = ft_find_width(format, info, i);
	i = ft_find_precision(format, info, i);
	i = ft_find_lenmod(format, info, i);
	return (i);
}
