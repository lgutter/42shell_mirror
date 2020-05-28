/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsub.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 17:15:42 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/17 17:15:44 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *string, unsigned int start, size_t len)
{
	char	*ret;
	size_t	index;

	index = 0;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	while (index < len)
	{
		ret[index] = string[start];
		index++;
		start++;
	}
	ret[index] = '\0';
	return (ret);
}
