/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlenc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/14 12:25:27 by lgutter       #+#    #+#                 */
/*   Updated: 2019/02/14 12:25:28 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlenc(const char *string, int delim, size_t size)
{
	size_t len;

	len = 0;
	while (string[len] != (char)delim && len < size)
		len++;
	return (len);
}
