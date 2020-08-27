/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/16 15:36:46 by lgutter       #+#    #+#                 */
/*   Updated: 2020/02/07 08:34:01 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *string)
{
	size_t len;

	len = 0;
	if (string == NULL)
		return (0);
	while (string[len] != '\0')
		len++;
	return (len);
}
