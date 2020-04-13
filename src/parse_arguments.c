/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_arguments.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/06 17:03:13 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"

t_argument			*free_arguments(t_argument *arguments)
{
	if (arguments == NULL)
		return (NULL);
	free(arguments->argument);
	arguments->argument = NULL;
	arguments->next = free_arguments(arguments->next);
	free(arguments);
	return (NULL);
}

static t_argument	*init_arguments(t_token **token)
{
	t_argument *arguments;

	arguments = (t_argument *)ft_memalloc(sizeof(t_argument) * 1);
	if (arguments == NULL)
	{
		handle_error(malloc_error);
		return (NULL);
	}
	arguments->argument = ft_strdup((*token)->value);
	if (arguments->argument == NULL)
	{
		free_arguments(arguments);
		handle_error(malloc_error);
		return (NULL);
	}
	arguments->next = NULL;
	return (arguments);
}

t_argument			*parse_arguments(t_token **token)
{
	t_argument	*arguments;

	if (token == NULL || *token == NULL || (*token)->type != WORD)
	{
		handle_error_str(parsing_error, (*token)->value);
		return (NULL);
	}
	arguments = init_arguments(token);
	if (arguments == NULL)
		return (handle_error_p(malloc_error, NULL));
	*token = (*token)->next;
	if (*token != NULL && (*token)->type == WORD)
	{
		arguments->next = parse_arguments(token);
		if (arguments->next == NULL)
		{
			free_arguments(arguments);
			return (NULL);
		}
	}
	return (arguments);
}
