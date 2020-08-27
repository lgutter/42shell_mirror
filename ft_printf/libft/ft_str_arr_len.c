/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_arr_len.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/21 11:49:18 by lgutter       #+#    #+#                 */
/*   Updated: 2020/01/21 11:49:21 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_str_arr_len(char **pointer_array)
{
	size_t index;

	index = 0;
	while (pointer_array[index] != NULL)
	{
		index++;
	}
	return (index);
}
