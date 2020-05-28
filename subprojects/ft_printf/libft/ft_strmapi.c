/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 20:02:03 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/16 20:02:04 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *string, char (*function)(unsigned int, char))
{
	unsigned int	index;
	char			*ret;

	index = 0;
	ret = (char *)malloc(sizeof(char) * ft_strlen(string) + 1);
	if (!ret)
		return (NULL);
	while (string[index] != '\0')
	{
		ret[index] = (*function)(index, string[index]);
		index++;
	}
	ret[index] = '\0';
	return (ret);
}
