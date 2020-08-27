/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/18 16:52:17 by lgutter       #+#    #+#                 */
/*   Updated: 2020/02/07 08:39:53 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strjoin_internal(char *ret, char const *str, size_t xedni)
{
	size_t index;

	index = 0;
	while (str[index] != '\0')
	{
		ret[xedni] = str[index];
		xedni++;
		index++;
	}
	return (xedni);
}

char			*ft_strjoin(char const *string1, char const *string2)
{
	char	*ret;
	size_t	in;
	size_t	dex;

	in = ft_strlen(string1);
	dex = ft_strlen(string2);
	ret = (char *)malloc(sizeof(char) * (in + dex + 1));
	if (!ret)
	{
		return (NULL);
	}
	ret[in + dex] = '\0';
	if (string1 == NULL && string2 != NULL)
		ret = ft_strncpy(ret, string2, dex);
	else if (string1 != NULL && string2 == NULL)
		ret = ft_strncpy(ret, string1, in);
	else if (string1 != NULL && string2 != NULL)
	{
		in = 0;
		in = ft_strjoin_internal(ret, string1, in);
		ft_strjoin_internal(ret, string2, in);
	}
	return (ret);
}
