/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcharjoin.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/27 12:13:40 by lgutter       #+#    #+#                 */
/*   Updated: 2019/11/16 15:35:45 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcharjoin(char *str, char c)
{
	char		*strnew;
	size_t		i;

	i = 0;
	strnew = ft_strnew(ft_strlen(str) + 2);
	if (strnew == NULL)
		return (NULL);
	while (i < ft_strlen(str))
	{
		strnew[i] = str[i];
		i++;
	}
	strnew[i] = c;
	strnew[i + 1] = '\0';
	return (strnew);
}
