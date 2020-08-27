/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 17:05:06 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/31 17:05:07 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long	ft_exceptions(unsigned long integer, const char *string)
{
	size_t	index;

	index = 0;
	if (*string == '+')
	{
		if (ft_isdigit(string[20]) == 1 && ft_isdigit(string[21]) == 1)
			return (0);
		if (integer > 9223372036854775807)
			return (0);
		return (integer);
	}
	if (*string == '-')
		string++;
	while (ft_isdigit(string[index]) != 0)
		index++;
	if (index > 19)
		return (0);
	if (integer > 9223372036854775807)
		return (0);
	return (1);
}

int						ft_atoi(const char *string)
{
	size_t			index;
	unsigned long	result;

	index = 0;
	result = 0;
	while (ft_iswhitespace(*string) == 1)
		string++;
	if (string[index] == '+' || string[index] == '-')
		index++;
	while (ft_isdigit(string[index]) != 0)
	{
		result = result * 10;
		result = result + (string[index] - 48);
		if (index == 19)
		{
			if (ft_exceptions(result, string) == 0 && string[0] != '-')
				return (-1);
			if (ft_exceptions(result, string) == 0)
				return (0);
		}
		index++;
	}
	if (string[0] == '-')
		return ((int)(result * -1));
	return ((int)result);
}
