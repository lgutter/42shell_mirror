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

size_t		insert_match(t_shell *shell, t_complete *comp)
{
	t_clist		*list;
	char		*insert;
	char		c;
	int			i;

	list = comp->list;
	i = comp->to_complen;
	if (i == 0)
		return (0);
	if (list->next == NULL && list->match != NULL && list->length != 0)
		insert = ft_strdup(&list->match[i]);
	else
	{
		while (list->match[i] != '\0')
		{
			c = list->match[i];
			while (list != NULL)
			{
				if (list->match[i] != c)
					insert = ft_strndup(&list->match[comp->to_complen + 1],
									i - comp->to_complen + 1);
				list = list->next;
			}
			i++;
			list = comp->list;
		}
		ft_printf("\n TESTinsert ==== %s \n\n", insert);
	}
	insert_word(shell->buffer, &shell->cursor, insert, ft_strlen(insert));
	return (0);
}
