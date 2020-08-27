/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/23 12:11:07 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/23 12:11:23 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa(int integer)
{
	size_t	len;
	char	*ret;

	ret = NULL;
	if (integer == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_nbrlenbase((long)integer, 10);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	if (integer < 0)
	{
		ret[0] = '-';
		integer *= -1;
	}
	ret[len] = '\0';
	len--;
	while (integer / 10 != 0)
	{
		ret[len] = ((integer % 10) + 48);
		integer /= 10;
		len--;
	}
	ret[len] = (integer + 48);
	return (ret);
}
