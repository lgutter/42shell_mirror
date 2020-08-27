/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/28 12:22:38 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/28 12:22:39 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst < src)
	{
		dst = ft_memcpy(dst, src, len);
	}
	else
	{
		dst = ft_memrcpy(dst, src, len);
	}
	return (dst);
}
