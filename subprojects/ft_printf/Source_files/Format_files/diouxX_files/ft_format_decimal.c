/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_format_decimal.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 13:13:13 by lgutter       #+#    #+#                 */
/*   Updated: 2019/11/29 15:25:06 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_formatdecimal(t_info *info)
{
	long long	n;

	info->conv = 'd';
	if (info->precfound == 1 && (info->flags & e_zero) != 0)
		info->flags -= e_zero;
	if ((info->lenmod & e_hh) != 0)
	{
		n = (char)va_arg(info->arguments, int);
	}
	else if ((info->lenmod & e_h) != 0)
	{
		n = (short)va_arg(info->arguments, int);
	}
	else if ((info->lenmod & e_ll) != 0 || (info->lenmod & e_l) != 0)
	{
		n = va_arg(info->arguments, long long);
	}
	else
	{
		n = (long long)va_arg(info->arguments, int);
	}
	return (ft_formatlonglong(n, info));
}
