/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_formatlonglongunsigned.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/19 09:51:50 by lgutter       #+#    #+#                 */
/*   Updated: 2019/11/29 15:24:05 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_formatlonglongunsigned(unsigned long long n, t_info *info)
{
	char	*nb;

	info->sign = 1;
	nb = ft_ulltoa_base_low(n, 10);
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
