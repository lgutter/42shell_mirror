/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_write_middle_width.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 14:24:14 by lgutter       #+#    #+#                 */
/*   Updated: 2019/12/04 16:43:07 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		print_padding(t_info *info, size_t len)
{
	while (len > 0)
	{
		info->writer(info->target, &info->totallen, " ", 1);
		len--;
	}
}

static void		write_middle_order(t_info *info, size_t len, char *str, char *o)
{
	while (*o != '\0')
	{
		if (*o == 's')
		{
			print_padding(info, len / 2);
		}
		else if (*o == 'l')
		{
			print_padding(info, len - (len / 2));
		}
		else if (*o == 'r')
		{
			ft_write_flags(info);
			info->writer(info->target, &info->totallen, str, 0);
		}
		o++;
	}
}

void			ft_write_middle_width(t_info *info, char *str)
{
	size_t		len;

	len = 0;
	if (info->width > 0 && info->width > info->len)
	{
		len = info->width - info->len;
		if (len % 2 == 0)
		{
			write_middle_order(info, len, str, "srs");
		}
		else
		{
			if ((info->flags & e_minus) != 0)
			{
				write_middle_order(info, len, str, "srl");
			}
			else
			{
				write_middle_order(info, len, str, "lrs");
			}
		}
	}
}
