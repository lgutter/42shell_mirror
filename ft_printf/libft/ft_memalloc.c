/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memalloc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/10 17:29:07 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/19 14:28:13 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char *string;

	string = (unsigned char *)malloc(size);
	if (!string)
		return (NULL);
	while (size > 0)
	{
		size--;
		string[size] = '\0';
	}
	return ((void *)string);
}
