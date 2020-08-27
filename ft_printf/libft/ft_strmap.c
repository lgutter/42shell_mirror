/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 15:32:17 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/16 15:32:18 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *string, char (*function)(char))
{
	int		index;
	char	*ret;

	ret = (char *)malloc(sizeof(char) * ft_strlen(string) + 1);
	if (!ret)
		return (NULL);
	index = 0;
	while (string[index] != '\0')
	{
		ret[index] = (*function)(string[index]);
		index++;
	}
	ret[index] = '\0';
	return (ret);
}
