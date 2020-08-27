/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nbrlenbase_ull.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/21 16:36:58 by ivan-tey      #+#    #+#                 */
/*   Updated: 2019/10/22 12:00:37 by ivan-tey      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_nbrlenbase_ull(unsigned long long number, int base)
{
	size_t len;

	len = 1;
	if (base == 1)
		return ((size_t)number + len);
	while (number / base != 0)
	{
		len++;
		number /= base;
	}
	return (len);
}
