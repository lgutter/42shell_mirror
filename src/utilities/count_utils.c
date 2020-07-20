/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   count_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/19 20:08:37 by devan         #+#    #+#                 */
/*   Updated: 2020/07/19 20:08:37 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t		ft_index_nchar(char *string, char c, size_t n)
{
	size_t	i;

	i = 0;
	if (string == NULL || n == 0 || c == '\0')
		return (0);
	while (string[i] != '\0')
	{
		if (string[i] == c)
			n--;
		if (n == 0)
			break ;
		i++;
	}
	if (string[i] == '\0')
		i = 0;
	return (i);
}

size_t		ft_countchar(char *string, char c)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	if (string == NULL || c == '\0')
		return (0);
	while (string[i] != '\0')
	{
		if (string[i] == c)
			count++;
		i++;
	}
	return (count);
}
