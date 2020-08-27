/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/21 19:46:22 by lgutter       #+#    #+#                 */
/*   Updated: 2020/01/21 19:47:55 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *string, size_t len)
{
	char	*ret;
	size_t	index;

	index = 0;
	if (string == NULL)
	{
		return (NULL);
	}
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret != NULL)
	{
		while (index < len)
		{
			ret[index] = string[index];
			index++;
		}
		ret[index] = '\0';
	}
	return (ret);
}
