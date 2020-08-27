/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/25 21:31:21 by lgutter       #+#    #+#                 */
/*   Updated: 2020/02/04 17:37:31 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int delim, size_t len)
{
	size_t				index;
	unsigned char		*output;
	unsigned const char	*input;

	input = src;
	output = dst;
	index = 0;
	while (index < len && input[index] != (unsigned char)delim)
	{
		output[index] = input[index];
		index++;
	}
	if (index == len)
	{
		return (NULL);
	}
	else
	{
		output[index] = input[index];
		index++;
		return ((void *)&output[index]);
	}
}
