/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_formatlonglong.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 14:35:42 by lgutter       #+#    #+#                 */
/*   Updated: 2019/11/29 15:24:02 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_format_neglonglong(long long n, t_info *info)
{
	char *nb;

	info->sign = -1;
	if ((info->flags & e_zero) != 0)
	{
		info->writer(info->target, &info->totallen, "-", 1);
		info->len = 1;
		n = n * -1;
	}
	else
		info->len = 0;
	nb = ft_itoa_base(n, 10);
	if (info->precfound > 0)
		nb = ft_precision_int(info, nb);
	if (nb == NULL)
		return (-1);
	info->len += ft_strlen(nb);
	if ((info->flags & e_minus) != 0)
		ft_write_order(info, nb, "rw");
	else
		ft_write_order(info, nb, "wr");
	free(nb);
	return (0);
}

int			ft_formatlonglong(long long n, t_info *info)
{
	char	*nb;

	if (n < 0)
		return (ft_format_neglonglong(n, info));
	info->sign = 1;
	nb = ft_itoa_base(n, 10);
	if (info->precfound > 0)
		nb = ft_precision_int(info, nb);
	if (nb == NULL)
		return (-1);
	info->len = ft_strlen(nb);
	if ((info->flags & e_plus) != 0 || (info->flags & e_space) != 0)
		info->len++;
	if ((info->flags & e_minus) != 0)
		ft_write_order(info, nb, "frw");
	else
	{
		if ((info->flags & e_zero) != 0)
			ft_write_order(info, nb, "fwr");
		else
			ft_write_order(info, nb, "wfr");
	}
	free(nb);
	return (0);
}
