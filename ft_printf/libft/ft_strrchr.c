/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 11:17:51 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/31 11:17:52 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int character)
{
	size_t index;

	index = ft_strlen(string);
	if (character == '\0')
	{
		return ((char *)&string[index]);
	}
	while (index > 0)
	{
		if (string[index] == character)
		{
			return ((char *)&string[index]);
		}
		index--;
	}
	if (string[index] == character)
	{
		return ((char *)&string[index]);
	}
	return (NULL);
}
