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

static void	insert_node(struct s_ari_node *const new_node,
				struct s_ari_node **const node_list)
{
	struct s_ari_node	*iterator;

	if (*node_list == NULL)
	{
		*node_list = new_node;
	}
	else
	{
		iterator = *node_list;
		while (iterator->next != NULL)
		{
			iterator = iterator->next;
		}
		iterator->next = new_node;
		new_node->prev = iterator;
	}
}

int			arithmatic_add_token(struct s_ari_node **const node_list,
				char *const original_key,
				const long int value,
				const enum e_operator operator)
{
	struct s_ari_node	*new_node;

	new_node = ft_memalloc(sizeof(*new_node));
	if (new_node == NULL)
	{
		return (malloc_error);
	}
	if (original_key)
	{
		new_node->original_key = ft_strdup(original_key);
		if (new_node->original_key == NULL)
		{
			free(new_node);
			return (malloc_error);
		}
	}
	new_node->value = value;
	new_node->operator = operator;
	insert_node(new_node, node_list);
	return (0);
}
