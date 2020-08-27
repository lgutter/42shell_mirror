/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdel.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/02 21:36:33 by lgutter       #+#    #+#                 */
/*   Updated: 2019/02/02 21:36:34 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **start, void (*del)(void *, size_t))
{
	t_list *current;
	t_list *temp;

	current = *start;
	while (current != NULL)
	{
		temp = current->next;
		(*del)(current->content, current->content_size);
		free(current);
		current = NULL;
		if (temp != NULL)
		{
			current = temp;
		}
		else
		{
			*start = NULL;
			return ;
		}
	}
}
