/* ************************************************************************** */
/*                                                                            */
/*   cetushell - 21 Shell                                 ::::::::            */
/*                                                      :+:    :+:            */
/*   By: dkroeke <dkroeke@student.codam.nl>            +:+                    */
/*       lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*                                                 #+#    #+#                 */
/*   License: GPLv3                                ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"

void	ft_swap_rv(t_buff *buffer)
{
	size_t 		temp;

	if (buffer->rv_start < buffer->rv_end)
	{
		temp = buffer->rv_start;
		buffer->rv_start = buffer->rv_end;
		buffer->rv_end = temp;
		buffer->rv_start++;
	}
}