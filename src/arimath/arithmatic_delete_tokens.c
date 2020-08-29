/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arimath.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 10:58:15 by aholster      #+#    #+#                 */
/*   Updated: 2020/04/20 10:58:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "arimath.h"

void	arithmatic_delete_tokens(struct s_ari_node **const node_list)
{
	struct s_ari_node	*trail;

	while (*node_list != NULL)
	{
		trail = *node_list;
		*node_list = (*node_list)->next;
		free(trail->original_key);
		ft_bzero(trail, sizeof(*trail));
		free(trail);
	}
}
