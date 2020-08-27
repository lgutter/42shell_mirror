/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_format_unsigneddecimal.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/19 09:54:43 by lgutter       #+#    #+#                 */
/*   Updated: 2019/11/29 15:28:10 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_format_unsigneddecimal(t_info *info)
{
	unsigned long long	n;

	info->conv = 'u';
	if (info->precfound == 1 && (info->flags & e_zero) != 0)
		info->flags -= e_zero;
	if ((info->lenmod & e_hh) != 0)
	{
		n = (unsigned char)va_arg(info->arguments, unsigned int);
	}
	else if ((info->lenmod & e_h) != 0)
	{
		n = (unsigned short)va_arg(info->arguments, unsigned int);
	}
	else if ((info->lenmod & e_ll) != 0 || (info->lenmod & e_l) != 0)
	{
		n = va_arg(info->arguments, unsigned long long);
	}
	else
	{
		n = (unsigned long long)va_arg(info->arguments, unsigned int);
	}
	return (ft_formatlonglongunsigned(n, info));
}
