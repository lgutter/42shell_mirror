/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/30 19:39:45 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/30 19:39:46 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t index;
	size_t xedni;
	size_t ret;

	ret = ft_strlen(dst);
	xedni = 0;
	if (size <= ret)
	{
		return (size + ft_strlen(src));
	}
	index = ret;
	while (index < (size - 1) && src[xedni] != '\0')
	{
		dst[index] = src[xedni];
		index++;
		xedni++;
	}
	dst[index] = '\0';
	return (ret + ft_strlen(src));
}
