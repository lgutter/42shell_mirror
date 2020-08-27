/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcdup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:47:04 by lgutter       #+#    #+#                 */
/*   Updated: 2020/01/21 19:50:31 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(const char *string, char delim)
{
	size_t	len;

	if (string == NULL)
	{
		return (NULL);
	}
	len = ft_strlenc(string, delim, ft_strlen(string));
	return (ft_strndup(string, len));
}
