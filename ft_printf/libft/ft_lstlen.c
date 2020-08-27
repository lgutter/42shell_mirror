/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/03 17:55:46 by lgutter       #+#    #+#                 */
/*   Updated: 2019/02/03 17:55:47 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstlen(t_list **start)
{
	t_list	*current;
	size_t	index;

	index = 1;
	current = *start;
	while (current->next != NULL)
	{
		current = current->next;
		index++;
	}
	return (index);
}
