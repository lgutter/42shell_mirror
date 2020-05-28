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

void	*ft_memset(void *input, int setvalue, size_t len)
{
	unsigned char	*str;
	size_t			index;

	str = input;
	index = 0;
	while (index < len)
	{
		str[index] = setvalue;
		index++;
	}
	return (str);
}
