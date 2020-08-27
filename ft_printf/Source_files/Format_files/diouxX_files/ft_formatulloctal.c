/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_formatulloctal.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 12:02:41 by ivan-tey      #+#    #+#                 */
/*   Updated: 2019/11/29 15:23:57 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	zero_exception(t_info *info, unsigned long long n)
{
	if ((n == 0 && (info->precfound < 0 || info->precision != 0))
		|| (info->len < info->width && (info->flags & e_zero) != 0))
	{
		info->flags -= e_hash;
	}
	else
		info->len += 1;
}

int			ft_formatulloctal(unsigned long long n, t_info *info)
{
	char	*nb;

	info->sign = 1;
	nb = ft_ulltoa_base_low(n, 8);
	if (info->precfound > 0)
		nb = ft_precision_int(info, nb);
	if (nb == NULL)
		return (-1);
	info->len = ft_strlen(nb);
	if ((info->flags & e_hash) != 0)
		zero_exception(info, n);
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
