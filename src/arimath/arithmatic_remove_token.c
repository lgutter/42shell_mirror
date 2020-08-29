/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arithmatic_expansion.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 10:58:15 by aholster      #+#    #+#                 */
/*   Updated: 2020/04/20 10:58:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "arimath.h"

void		arithmatic_remove_token(struct s_ari_node *anode)
{
	if (anode->prev)
	{
		anode->prev->next = anode->next;
	}
	if (anode->next)
	{
		anode->next->prev = anode->prev;
	}
	free(anode->original_key);
	ft_bzero(anode, sizeof(*anode));
	free(anode);
}
