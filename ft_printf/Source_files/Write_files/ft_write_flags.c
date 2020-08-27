/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_write_flags.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 13:52:57 by lgutter       #+#    #+#                 */
/*   Updated: 2019/11/29 09:27:24 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_float_flags(t_info *info)
{
	if ((info->flags & e_plus) != 0 && info->sign == 1)
		info->writer(info->target, &info->totallen, "+", 1);
	else if ((info->flags & e_space) != 0 && info->sign == 1)
		info->writer(info->target, &info->totallen, " ", 1);
	else if (info->sign == -1)
		info->writer(info->target, &info->totallen, "-", 1);
}

void		ft_write_flags(t_info *info)
{
	if ((info->conv == 'd' || info->conv == 'i' || info->conv == 'u')
		&& info->sign >= 0)
	{
		if (info->flags & e_plus)
			info->writer(info->target, &info->totallen, "+", 1);
		else if (info->flags & e_space)
			info->writer(info->target, &info->totallen, " ", 1);
	}
	if (info->conv == 'x' || info->conv == 'X' || info->conv == 'p')
	{
		if ((info->flags & e_hash) && info->conv == 'X')
			info->writer(info->target, &info->totallen, "0X", 0);
		else if (info->conv == 'p' ||
				((info->flags & e_hash) && info->conv == 'x'))
			info->writer(info->target, &info->totallen, "0x", 0);
	}
	if (info->conv == 'o' && (info->flags & e_hash) != 0)
		info->writer(info->target, &info->totallen, "0", 1);
	if (info->conv == 'f')
	{
		ft_float_flags(info);
	}
}
