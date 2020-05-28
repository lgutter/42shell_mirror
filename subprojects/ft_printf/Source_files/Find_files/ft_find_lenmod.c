/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_find_lenmod.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 10:06:39 by ivan-tey      #+#    #+#                 */
/*   Updated: 2019/11/11 18:19:03 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_find_lenmod(const char *format, t_info *info, int i)
{
	while (format[i] != '\0')
	{
		if (format[i] == 'L')
			info->lenmod |= e_L;
		else if (format[i] == 'l' && format[i + 1] != 'l')
			info->lenmod |= e_l;
		else if (format[i] == 'l' && format[i + 1] == 'l')
		{
			info->lenmod |= e_ll;
			i += 2;
			return (i);
		}
		else if (format[i] == 'h' && format[i + 1] != 'h')
			info->lenmod |= e_h;
		else if (format[i] == 'h' && format[i + 1] == 'h')
		{
			info->lenmod |= e_hh;
			i += 2;
			return (i);
		}
		else
			return (i);
		i++;
	}
	return (i);
}
