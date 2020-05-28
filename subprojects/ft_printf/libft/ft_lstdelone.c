/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_delone.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/02 14:31:58 by lgutter       #+#    #+#                 */
/*   Updated: 2019/02/02 14:31:59 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (del != NULL)
	{
		(*del)((*alst)->content, (*alst)->content_size);
	}
	free(*alst);
	*alst = NULL;
}
