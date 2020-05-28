/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/02 12:25:13 by lgutter       #+#    #+#                 */
/*   Updated: 2019/02/02 12:25:14 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list) * 1);
	if (new == NULL)
	{
		return (NULL);
	}
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
		new->next = NULL;
		return (new);
	}
	new->content = ft_memdup(content, content_size);
	if (new->content == NULL)
	{
		free(new);
		new = NULL;
		return (NULL);
	}
	new->content_size = content_size;
	new->next = NULL;
	return (new);
}
