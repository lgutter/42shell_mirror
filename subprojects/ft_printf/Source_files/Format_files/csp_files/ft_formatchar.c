/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_formatchar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 16:40:16 by lgutter       #+#    #+#                 */
/*   Updated: 2019/11/29 12:59:23 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_formatchar(t_info *info)
{
	char c;

	info->conv = 'c';
	c = (char)va_arg(info->arguments, int);
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
