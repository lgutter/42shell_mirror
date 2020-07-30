/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_assignments.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/06 17:03:13 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"
#include "utils.h"

t_assignment		*free_assignments(t_assignment *assignment)
{
	if (assignment == NULL)
		return (NULL);
	free(assignment->key);
	assignment->key = NULL;
	free(assignment->value);
	assignment->value = NULL;
	free(assignment->original);
	assignment->original = NULL;
	assignment->next = free_assignments(assignment->next);
	free(assignment);
	return (NULL);
}

static t_assignment	*init_assignment(char *word)
{
	t_assignment *assignment;

	assignment = (t_assignment *)ft_memalloc(sizeof(t_assignment) * 1);
	if (assignment == NULL)
	{
		handle_error(malloc_error);
		return (NULL);
	}
	assignment->key = ft_strndup(word, (ft_strchr(word, '=') - word));
	assignment->value = ft_strdup(ft_strchr(word, '=') + 1);
	if (assignment->key == NULL || assignment->value == NULL)
	{
		free_assignments(assignment);
		handle_error(malloc_error);
		return (NULL);
	}
	assignment->next = NULL;
	return (assignment);
}

t_assignment		*parse_assignments(t_token **token)
{
	t_assignment	*assignment;

	if (token == NULL || *token == NULL)
		return (handle_error_p(invalid_token, NULL));
	if ((*token)->type != WORD)
	{
		handle_error_str(parsing_error, (*token)->value);
		return (NULL);
	}
	assignment = init_assignment((*token)->value);
	if (assignment == NULL)
		return (NULL);
	*token = (*token)->next;
	if (*token != NULL && (*token)->type == WORD &&
												is_assignment((*token)->value))
	{
		assignment->next = parse_assignments(token);
		if (assignment->next == NULL)
		{
			free_assignments(assignment);
			return (NULL);
		}
	}
	return (assignment);
}
