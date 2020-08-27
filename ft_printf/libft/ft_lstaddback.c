/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstaddback.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/03 17:40:03 by lgutter       #+#    #+#                 */
/*   Updated: 2019/02/03 17:40:04 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddback(t_list **start, t_list *new)
{
	t_list	*current;

	current = *start;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
}
