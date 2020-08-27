/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnequ.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 15:49:40 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/17 15:49:44 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *str1, char const *str2, size_t len)
{
	size_t index;

	index = 0;
	if (len == 0)
		return (1);
	else
	{
		while (str1[index] != '\0' && str2[index] != '\0' && index < (len - 1))
		{
			if (str1[index] != str2[index])
			{
				return (0);
			}
			index++;
		}
		if (str1[index] != str2[index])
		{
			return (0);
		}
		return (1);
	}
}
