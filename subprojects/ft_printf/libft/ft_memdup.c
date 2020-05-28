/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/02 11:32:38 by lgutter       #+#    #+#                 */
/*   Updated: 2019/02/02 11:32:39 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *source, size_t len)
{
	size_t				index;
	unsigned char		*ret;
	const unsigned char	*input;

	index = 0;
	input = (const unsigned char *)source;
	ret = (void *)ft_memalloc(sizeof(unsigned char) * len);
	if (ret == NULL)
	{
		return (NULL);
	}
	while (index < len)
	{
		ret[index] = input[index];
		index++;
	}
	return ((void *)ret);
}
