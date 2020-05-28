/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_formatpointer.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 14:33:13 by ivan-tey      #+#    #+#                 */
/*   Updated: 2019/11/29 15:32:06 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_formatpointer(t_info *info)
{
	unsigned long long	p;
	char				*pt;

	pt = NULL;
	p = 0;
	info->conv = 'p';
	p = va_arg(info->arguments, unsigned long long);
	pt = ft_ulltoa_base_low(p, 16);
	if (info->precfound > 0)
		pt = ft_precision_int(info, pt);
	if (pt == NULL)
		return (-1);
	info->len = ft_strlen(pt) + 2;
	if ((info->flags & e_minus) != 0)
		ft_write_order(info, pt, "frw");
	else
	{
		if ((info->flags & e_zero) != 0)
			ft_write_order(info, pt, "fwr");
		else
			ft_write_order(info, pt, "wfr");
	}
	free(pt);
	return (0);
}
