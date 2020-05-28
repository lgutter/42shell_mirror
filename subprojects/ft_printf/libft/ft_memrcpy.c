/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memrcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/28 18:33:50 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/28 18:33:55 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrcpy(void *dst, const void *src, size_t len)
{
	unsigned char		*output;
	unsigned const char	*input;

	output = dst;
	input = src;
	while (len > 0)
	{
		output[len - 1] = input[len - 1];
		len--;
	}
	return (dst);
}
