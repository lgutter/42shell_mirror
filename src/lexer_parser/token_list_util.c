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
#include "vecstr.h"

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

t_token			*free_token_list_empty_buff(t_token **start, t_vecstr *buff)
{
	free_token_list(start);
	clear_vecstr(buff);
	return (NULL);
}

static t_token	*init_token(t_token **start)
{
	t_token *temp;

	if (*start == NULL)
	{
		*start = (t_token *)ft_memalloc(sizeof(t_token) * 1);
		temp = *start;
	}
	else
	{
		temp = *start;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = (t_token *)ft_memalloc(sizeof(t_token) * 1);
		temp = temp->next;
	}
	return (temp);
}

int				add_token(t_token **start, t_type type, t_vecstr *buff)
{
	t_token *temp;

	if (start == NULL || buff == NULL)
		return (-1);
	temp = init_token(start);
	if (temp == NULL)
	{
		clear_vecstr(buff);
		return (malloc_error);
	}
	temp->next = NULL;
	temp->type = type;
	temp->value = ft_strdup(buff->string);
	clear_vecstr(buff);
	return (0);
}
