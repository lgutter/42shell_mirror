/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list_util.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:52:43 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/14 11:52:43 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token			*free_token_list(t_token **start)
{
	t_token	*temp;
	t_token	*current;

	if (start == NULL || *start == NULL)
		return (NULL);
	current = *start;
	while (current != NULL)
	{
		temp = current->next;
		free(current->value);
		current->type = 0;
		current->value = NULL;
		free(current);
		current = temp;
	}
	*start = NULL;
	return (NULL);
}

static t_token	*init_token(t_token **start)
{
	t_token *temp;
	t_token *previous;

	previous = NULL;
	if (*start == NULL)
	{
		*start = (t_token *)ft_memalloc(sizeof(t_token));
		temp = *start;
	}
	else
	{
		temp = *start;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = (t_token *)ft_memalloc(sizeof(t_token));
		previous = temp;
		temp = temp->next;
	}
	if (temp != NULL)
		temp->prev = previous;
	return (temp);
}

int				add_token(t_token **start, t_type type, char **buff)
{
	t_token *temp;

	temp = init_token(start);
	if (temp == NULL)
	{
		ft_memset((void *)*buff, '\0', ft_strlen(*buff));
		return (handle_error(malloc_error));
	}
	temp->next = NULL;
	temp->type = type;
	temp->value = ft_strdup(*buff);
	ft_memset((void *)*buff, '\0', ft_strlen(*buff));
	return (0);
}
