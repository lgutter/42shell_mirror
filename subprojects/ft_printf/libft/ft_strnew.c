/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 20:40:25 by lgutter       #+#    #+#                 */
/*   Updated: 2019/11/19 14:14:50 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *string;

	size++;
	string = (char *)malloc(sizeof(char) * (size + 1));
	if (!string)
		return (NULL);
	if (size > 0)
		size++;
	while (size > 0)
	{
		size--;
		string[size] = '\0';
	}
	return (string);
}
