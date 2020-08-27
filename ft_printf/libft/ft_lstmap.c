/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/03 17:33:24 by lgutter       #+#    #+#                 */
/*   Updated: 2019/02/03 17:33:26 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *list, t_list *(*f)(t_list *elem))
{
	t_list	*new;

	new = (f)(list);
	list = list->next;
	while (list->next != NULL)
	{
		ft_lstaddback(&new, (f)(list));
		list = list->next;
	}
	ft_lstaddback(&new, (f)(list));
	return (new);
}
