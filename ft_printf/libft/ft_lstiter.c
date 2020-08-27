/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/03 17:12:32 by lgutter       #+#    #+#                 */
/*   Updated: 2019/02/03 17:12:33 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *list, void (*f)(t_list *elem))
{
	while (list->next != NULL)
	{
		(f)(list);
		list = list->next;
	}
	(f)(list);
}
