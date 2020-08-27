/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memdel.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 16:43:15 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/13 16:43:17 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memdel(void **pointer)
{
	free(*pointer);
	*pointer = NULL;
}
