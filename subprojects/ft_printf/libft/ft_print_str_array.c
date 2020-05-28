/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_str_array.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 10:51:17 by lgutter       #+#    #+#                 */
/*   Updated: 2020/01/31 10:53:46 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_print_str_array(char **array)
{
	size_t index;

	index = 0;
	if (array == NULL || array[0] == NULL)
		return (-1);
	while (array[index] != NULL)
	{
		ft_printf("%s\n", array[index]);
		index++;
	}
	return (0);
}
