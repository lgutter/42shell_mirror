/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/25 19:00:57 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/25 19:01:02 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t				index;
	unsigned char		*output;
	unsigned const char	*input;

	output = dst;
	input = src;
	index = 0;
	while (index < len)
	{
		output[index] = input[index];
		index++;
	}
	return (dst);
}
