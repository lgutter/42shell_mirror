/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/30 12:05:07 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/30 12:05:08 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*ret;
	size_t	index;

	index = ft_strlen(src) + 1;
	if (len >= index)
	{
		ret = ft_memcpy(dst, src, index);
		while (index < len)
		{
			ret[index] = '\0';
			index++;
		}
		return (ret);
	}
	return (ft_memcpy(dst, src, len));
}
