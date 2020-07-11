/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   auto_complete_insert.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: devan <devan@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/01 21:43:33 by devan         #+#    #+#                 */
/*   Updated: 2020/07/01 21:43:33 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "input_handling.h"
#include "autocomplete.h"
#include "prompt.h"

static int			match_till(t_complete *comp, char *word)
{
	int		i;
	t_clist *list;

	i = 0;
	list = comp->list;
	while (word[i] != '\0')
	{
		while (list != NULL)
		{
			if (list->match[i] != word[i] && i != 0)
				return (i - 1);
			list = list->next;
		}
		i++;
		list = comp->list;
	}
	return (i);
}

static size_t		update_to_complete(t_complete *comp)
{
	int			i;
	char		*complete;
	size_t		len;

	if ((comp->options & SHELL_VAR) != 0)
		return (0);
	i = (int)comp->to_complen - 1;
	if (comp->to_complen != 0)
		while (comp->to_complete[i] != '/' && i > -1)
			i--;
	if (comp->to_complen == 0)
		complete = ft_strdup("");
	else
		complete = ft_strdup(&comp->to_complete[i + 1]);
	if (complete == NULL)
		return (1);
	len = ft_strlen(complete);
	free(comp->to_complete);
	comp->to_complete = ft_strdup(complete);
	comp->to_complen = len;
	free(complete);
	if (len == 0)
		return (1);
	return (0);
}

size_t				insert_match(t_shell *shell, t_complete *comp)
{
	char		*insert;
	int			i;

	insert = NULL;
	if (shell == NULL || shell->env == NULL || comp == NULL ||
		comp->list == NULL || comp->to_complete == NULL ||
		update_to_complete(comp) != 0 || comp->list->match == NULL)
		return (1);
	if (comp->list->next == NULL && comp->list->match != NULL &&
			comp->list->length != 0)
		insert = ft_strdup(&comp->list->match[comp->to_complen]);
	else
	{
		i = match_till(comp, comp->list->match);
		if (i <= (int)comp->to_complen)
			return (0);
		insert = ft_strndup(&comp->list->match[comp->to_complen],
								i - comp->to_complen);
	}
	if (insert == NULL || insert_word(shell->buffer, &shell->cursor, insert,
			ft_strlen(insert)) != 0)
		return (1);
	free(insert);
	return (0);
}
