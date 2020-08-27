/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/23 17:03:03 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/23 17:03:12 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl(char const *string)
{
	write(1, string, ft_strlen(string));
	write(1, "\n", 1);
}
