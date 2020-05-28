/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_find_width.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 13:57:09 by ivan-tey      #+#    #+#                 */
/*   Updated: 2019/11/27 18:07:54 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_find_width(const char *format, t_info *info, int i)
{
	int	nb;

	nb = 0;
	if (format[i] == '*')
	{
		nb = va_arg(info->arguments, int);
		if (nb < 0)
		{
			info->flags |= e_minus;
			nb *= -1;
		}
		i++;
	}
	else
	{
		nb = ft_atoi(&format[i]);
		if (nb > 0)
		{
			i += ft_nbrlenbase(nb, 10);
		}
	}
	info->width = nb;
	return (i);
}
