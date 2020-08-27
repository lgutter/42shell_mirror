/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/24 17:03:46 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/24 17:03:55 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *target, int setvalue, size_t len)
{
	size_t				i;
	size_t				chunk_size;
	unsigned long long	chunk;

	chunk = 0;
	chunk_size = sizeof(unsigned long long);
	i = chunk_size / sizeof(unsigned char);
	while (i > 0)
	{
		chunk <<= 8;
		chunk |= (unsigned long long)(unsigned char)setvalue;
		i--;
	}
	i = target == NULL ? len : 0;
	while (len >= chunk_size && i < (len - chunk_size))
	{
		*(unsigned long long *)&(((unsigned char *)target)[i]) = chunk;
		i += chunk_size;
	}
	while (i < len)
	{
		((unsigned char *)target)[i] = (unsigned char)setvalue;
		i++;
	}
	return (target);
}
