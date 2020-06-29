/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_complete_lists.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/29 05:24:17 by devan         #+#    #+#                 */
/*   Updated: 2020/06/29 05:24:17 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "autocomplete.h"

void    debug_complete_list(t_complete *comp)
{
	t_clist *list;
	static size_t  i = 0;

	list = comp->list;
	if (comp == NULL || comp->list == NULL)
		return ;
	ft_printf("\n");
	while (list != NULL)
	{
		ft_printf("%-*s ", comp->max_len + 1, list->match);
		list = list->next;
	}
	ft_printf("\n");
	i++;
}

static size_t	check_duplicate(t_clist *head, char *match)
{
	t_clist		*start;

	start = head;
	while (start != NULL)
	{
		if (start->match != NULL && ft_strcmp(match, start->match) == 0)
			return (1);
		start = start->next;
	}
	return (0);
}

static t_clist	*add_next_complete(t_clist *head, char *match)
{
	if (head->length != 0)
	{
		while (head->next != NULL)
			head = head->next;
		head->next = (t_clist *)ft_memalloc(sizeof(t_clist));
		if (head->next == NULL)
			return (NULL);
		head = head->next;
	}
	head->match = ft_strdup(match);
	if (head->match == NULL)
		return (NULL);
	return (head);
}

size_t			add_complete_list(t_complete *comp, char *match)
{
	t_clist *head;

	head = comp->list;
	if (head == NULL || match == NULL)
		return (1);
	if (check_duplicate(head, match) != 0)\
		return (1);
	head = add_next_complete(head, match);
	if (head == NULL)
		return (1);
	head->length = ft_strlen(match);
	if (head->length > comp->max_len)
		comp->max_len = head->length;
	return (0);
}
