/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_formatunknown.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/27 17:35:37 by lgutter       #+#    #+#                 */
/*   Updated: 2019/11/29 12:59:23 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_formatunknown(t_info *info, char c)
{
	info->len = 1;
	if (c == '\0')
		return (0);
	if ((info->flags & e_minus) != 0)
	{
		info->writer(info->target, &info->totallen, &c, 1);
		ft_write_width(info, 1);
	}
	else
	{
		ft_write_width(info, 1);
		info->writer(info->target, &info->totallen, &c, 1);
	}
	return (0);
}
