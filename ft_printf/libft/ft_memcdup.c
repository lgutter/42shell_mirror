/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcdup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/14 12:22:13 by lgutter       #+#    #+#                 */
/*   Updated: 2019/02/14 12:22:13 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcdup(const void *source, int delim, size_t size)
{
	return (ft_memdup(source, ft_strlenc((char *)source, delim, size)));
}
