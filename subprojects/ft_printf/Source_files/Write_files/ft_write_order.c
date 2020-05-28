/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_write_order.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/16 15:54:51 by lgutter       #+#    #+#                 */
/*   Updated: 2019/12/04 16:34:38 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	This function is used to call the following function the needed order:
**	- ft_write_[f]lags	|	f
**	- info->w[r]iter	|	r
**	- ft_check_[w]idth	|	w
**
**	Any order will be parsed, but if a character in the order string is
**	not recognized, the function returns -1 right away.
**	multiple calls to the same function will also be processed, so be careful!
*/

int	ft_write_order(t_info *info, char *str, char *order)
{
	while (*order != '\0')
	{
		if (*order == 'f' && (info->flags & e_middle) == 0)
		{
			ft_write_flags(info);
		}
		else if (*order == 'w' && (info->flags & e_middle) == 0)
		{
			ft_write_width(info, info->len);
		}
		else if (*order == 'r')
		{
			if ((info->flags & e_middle) != 0)
			{
				ft_write_middle_width(info, str);
			}
			else
			{
				info->writer(info->target, &info->totallen, str, 0);
			}
		}
		order++;
	}
	return (0);
}
