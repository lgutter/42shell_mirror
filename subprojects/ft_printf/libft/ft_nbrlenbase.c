/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nbrlenbase.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/02 12:11:46 by lgutter       #+#    #+#                 */
/*   Updated: 2019/11/13 13:10:30 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_nbrlenbase(long long number, int base)
{
	size_t len;

	len = 1;
	if (number < 0)
		len++;
	if (base == 1)
	{
		if (number < 0)
			number = number * -1;
		return ((size_t)number + len);
	}
	while (number / base != 0)
	{
		len++;
		number /= base;
	}
	return (len);
}
