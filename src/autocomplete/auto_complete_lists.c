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
    while (list != NULL)
    {
        int fd = open("test", O_CREAT | O_APPEND | O_WRONLY, 0644);
	    ft_dprintf(fd, "TESTLIST(%d) == (%s), (%d) \n", i, list->match, list->length);
	    close(fd);
        list = list->next;
    }
    i++;
}

int		add_complete_list(t_complete *comp, char *match)
{
	t_clist *head;

	head = comp->list;
	if (head == NULL || match == NULL)
		return (1);
	if (head->length != 0)
	{
		while (head->next != NULL)
			head = head->next;
		head->next = (t_clist *)ft_memalloc(sizeof(t_clist));
		if (head->next == NULL)
			return (1);
		head = head->next;
	}
	head->match = ft_strdup(match);
	if (head->match == NULL)
		return (1);
	head->length = ft_strlen(match);
	if (head->length > comp->max_len)
		comp->max_len = head->length;
	return (0);
}
