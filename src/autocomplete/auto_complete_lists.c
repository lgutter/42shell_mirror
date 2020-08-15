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
#include "input_handling.h"
#include "prompt.h"

size_t			scroll_cursor(t_cursor *cursor)
{
	if (cursor->current.y < cursor->max.y)
		ft_dprintf(STDERR_FILENO, "\n");
	cursor->start.y++;
	cursor->current.y++;
	if (cursor->current.y > cursor->max.y)
	{
		send_terminal(TERM_DOWN);
		cursor->start.y--;
		cursor->current.y--;
	}
	return (0);
}

void			print_complete_list(t_shell *shell, t_complete *comp)
{
	t_clist			*list;
	size_t			col;
	size_t			i;

	if (shell == NULL || comp == NULL || comp->list == NULL ||
		comp->list->match == NULL || comp->list->next == NULL)
		return ;
	list = comp->list;
	col = ((shell->cursor.max.x - 2) / (comp->max_len + 1));
	i = col;
	while (list != NULL)
	{
		if (i >= col)
			i = scroll_cursor(&shell->cursor);
		if (comp->options & (VAR_DBRACK | VAR_DOLLAR))
			ft_dprintf(STDERR_FILENO, "%s%-*s ",
							((comp->options & VAR_DBRACK) ? "${" : "$"),
												(comp->max_len), list->match);
		else
			ft_dprintf(STDERR_FILENO, "%-*s ", comp->max_len, list->match);
		list = list->next;
		i++;
	}
	scroll_cursor(&shell->cursor);
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

	if (comp == NULL || comp->list == NULL || match == NULL)
		return (1);
	head = comp->list;
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
