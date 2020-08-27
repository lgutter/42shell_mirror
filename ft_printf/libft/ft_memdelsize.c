/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memdelsize.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/02 14:34:16 by lgutter       #+#    #+#                 */
/*   Updated: 2019/02/02 14:34:18 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memdelsize(void *pointer, size_t size)
{
	size_t			index;
	unsigned char	*input;

	index = 0;
	input = pointer;
	while (index < size)
	{
		input[index] = 0;
		index++;
	}
	free(pointer);
	pointer = NULL;
}
