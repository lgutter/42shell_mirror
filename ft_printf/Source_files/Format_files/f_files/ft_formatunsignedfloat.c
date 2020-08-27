/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_formatunsignedfloat.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/21 12:52:44 by ivan-tey      #+#    #+#                 */
/*   Updated: 2019/11/29 12:13:07 by ivan-tey      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_floaty_things(t_info *info, long double f,\
							unsigned long long n, char *nb)
{
	size_t	prec;
	char	*temp;

	prec = 0;
	temp = NULL;
	ft_strexpand(&nb, ".");
	while (f > 0 && (prec < (info->precision + 5)))
	{
		f = (f - n) * 10;
		n = (long long)f;
		temp = ft_ulltoa_base_low(n, 10);
		ft_strexpand(&nb, temp);
		free(temp);
		prec++;
	}
	nb = ft_float_precision(info, nb);
	info->len = ft_strlen(nb) + ft_correctlen(info);
	if ((info->flags & e_minus) != 0)
		ft_write_order(info, nb, "frw");
	else if ((info->flags & e_zero) != 0)
		ft_write_order(info, nb, "fwr");
	else
		ft_write_order(info, nb, "wfr");
	free(nb);
	return (0);
}

int			ft_formatunsignedfloat(t_info *info, long double f)
{
	unsigned long long	n;
	char				*nb;

	n = (unsigned long long)f;
	nb = ft_ulltoa_base_low(n, 10);
	info->len = ft_strlen(nb);
	if (info->precfound < 0)
		info->precision = 6;
	return (ft_floaty_things(info, f, n, nb));
}
