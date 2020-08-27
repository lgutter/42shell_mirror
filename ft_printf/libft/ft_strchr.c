/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 11:05:38 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/31 11:05:39 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int character)
{
	while (*string != '\0')
	{
		if (*string == character)
		{
			return ((char *)string);
		}
		string++;
	}
	if (character == '\0')
	{
		return ((char *)string);
	}
	return (NULL);
}
