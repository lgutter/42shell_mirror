/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/30 17:21:50 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/30 17:21:51 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *string1, const char *string2, size_t len)
{
	size_t index;
	size_t xedni;

	index = 0;
	xedni = 0;
	while (string1[index] != '\0')
	{
		index++;
	}
	while (string2[xedni] != '\0')
	{
		if (xedni == len)
		{
			string1[index] = '\0';
			return (string1);
		}
		string1[index] = string2[xedni];
		index++;
		xedni++;
	}
	string1[index] = '\0';
	return (string1);
}
