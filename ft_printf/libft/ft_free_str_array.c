/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_str_array.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:12:44 by lgutter       #+#    #+#                 */
/*   Updated: 2020/02/07 11:40:00 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_free_str_array(char **array)
{
	size_t index;

	index = 0;
	if (array != NULL)
	{
		while (array[index] != NULL)
		{
			free(array[index]);
			array[index] = NULL;
			index++;
		}
		free(array);
	}
	return (index);
}
