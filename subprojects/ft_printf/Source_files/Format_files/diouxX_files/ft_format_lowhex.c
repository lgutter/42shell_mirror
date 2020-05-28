/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_format_lowhex.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/19 10:45:07 by ivan-tey      #+#    #+#                 */
/*   Updated: 2019/11/29 15:25:51 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_format_lowhex(t_info *info)
{
	unsigned long long n;

	info->conv = 'x';
	if (info->precfound == 1 && (info->flags & e_zero) != 0)
		info->flags -= e_zero;
	if ((info->lenmod & e_hh) != 0)
	{
		n = (unsigned char)va_arg(info->arguments, int);
	}
	else if ((info->lenmod & e_h) != 0)
	{
		n = (unsigned short)va_arg(info->arguments, int);
	}
	else if ((info->lenmod & e_ll) != 0 || (info->lenmod & e_l) != 0)
	{
		n = va_arg(info->arguments, unsigned long long);
	}
	else
	{
		n = (unsigned int)va_arg(info->arguments, int);
	}
	return (ft_formatulllowhex(n, info));
}
