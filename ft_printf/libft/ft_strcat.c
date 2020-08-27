/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcat.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/30 15:28:00 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/30 15:28:02 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *string1, const char *string2)
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
		string1[index] = string2[xedni];
		index++;
		xedni++;
	}
	string1[index] = '\0';
	return (string1);
}
