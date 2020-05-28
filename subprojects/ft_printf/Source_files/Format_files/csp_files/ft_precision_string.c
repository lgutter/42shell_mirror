/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_precision_string.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/19 16:02:07 by lgutter       #+#    #+#                 */
/*   Updated: 2019/12/04 16:07:29 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_precision_string(t_info *info, char **string)
{
	if (info->precfound < 0)
	{
		return (ft_strlen(*string));
	}
	else if (info->precision < 1)
	{
		*string = ft_strdup("");
		return (0);
	}
	else if (ft_strlen(*string) > info->precision)
	{
		return (info->precision);
	}
	return (ft_strlen(*string));
}
