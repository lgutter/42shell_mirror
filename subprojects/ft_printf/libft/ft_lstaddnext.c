/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstaddnext.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/03 21:25:08 by lgutter       #+#    #+#                 */
/*   Updated: 2019/02/03 21:25:09 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstaddnext(t_list *current, t_list *new)
{
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
	return (new);
}
