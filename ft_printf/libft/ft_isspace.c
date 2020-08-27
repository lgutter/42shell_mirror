/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isspace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/28 11:48:01 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/28 11:48:01 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isspace(int character)
{
	if (character == '\t' || character == '\n' || character == '\v'
		|| character == '\f' || character == '\r' || character == ' ')
	{
		return (1);
	}
	return (0);
}
