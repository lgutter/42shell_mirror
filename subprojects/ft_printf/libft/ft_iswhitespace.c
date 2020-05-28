/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_iswhitespace.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/19 17:58:22 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/19 17:58:26 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iswhitespace(char character)
{
	if (character == '\n' || character == '\t' || character == ' ' ||
		character == '\v' || character == '\f' || character == '\r')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
