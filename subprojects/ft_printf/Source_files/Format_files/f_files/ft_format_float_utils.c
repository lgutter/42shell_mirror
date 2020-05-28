/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_float_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/27 12:36:45 by lgutter       #+#    #+#                 */
/*   Updated: 2019/11/27 12:57:16 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_correctlen(t_info *info)
{
	if (((info->flags & e_plus) != 0 && info->sign == 1) ||
		((info->flags & e_space) != 0 && info->sign == 1) ||
		(info->sign == -1))
	{
		return (1);
	}
	return (0);
}

int		ft_check_sign(long double f)
{
	t_floatunion	nb;

	nb.flnb = f;
	if ((nb.shnb[4] >> 15) == -1)
		return (1);
	return (0);
}
