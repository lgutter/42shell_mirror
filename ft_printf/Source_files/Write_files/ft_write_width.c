/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_write_width.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 18:36:06 by ivan-tey      #+#    #+#                 */
/*   Updated: 2019/11/29 12:12:12 by ivan-tey      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_write_width(t_info *info, size_t src_len)
{
	size_t		len;

	len = 0;
	if (info->width > 0 && info->width > src_len)
	{
		len = info->width - src_len;
		while (len > 0)
		{
			if ((info->flags & e_zero) != 0)
				info->writer(info->target, &info->totallen, "0", 1);
			else
				info->writer(info->target, &info->totallen, " ", 1);
			len--;
		}
	}
}
