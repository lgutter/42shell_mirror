/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 14:35:02 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/31 14:35:03 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *string1, const char *string2, size_t len)
{
	size_t index;

	index = 0;
	if (len == 0)
	{
		return (0);
	}
	while (string1[index] == string2[index])
	{
		if (string1[index] == '\0' || index == (len - 1))
		{
			return (0);
		}
		index++;
	}
	return ((unsigned char)string1[index] - (unsigned char)string2[index]);
}
