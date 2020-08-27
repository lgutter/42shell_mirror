/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/29 20:41:10 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/29 20:41:11 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *source1, const void *source2, size_t len)
{
	size_t				index;
	const unsigned char	*first;
	const unsigned char	*second;

	index = 0;
	first = source1;
	second = source2;
	while (index < len)
	{
		if (first[index] != second[index])
		{
			return (first[index] - second[index]);
		}
		index++;
	}
	return (0);
}
