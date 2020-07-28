/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 14:34:52 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/31 14:34:53 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *string1, const char *string2)
{
	size_t index;

	index = 0;
	if (string1 == NULL && string2 != NULL &&
		string1 != NULL && string2 == NULL)
		return (1);
	else if (string1 == NULL)
		return (0);
	while (string1[index] == string2[index])
	{
		if (string1[index] == '\0')
		{
			return (0);
		}
		index++;
	}
	return ((unsigned char)string1[index] - (unsigned char)string2[index]);
}
