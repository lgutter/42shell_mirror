/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_simple_command.c                             :+:    :+:            */
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

t_simple_cmd	*free_simple_command(t_simple_cmd *simple_command)
{
	if (simple_command != NULL)
	{
		simple_command->redirects = free_io_redirect(simple_command->redirects);
		simple_command->arguments = free_arguments(simple_command->arguments);
		free_assignments(simple_command->assignments);
		simple_command->assignments = NULL;
		free_dchar_arr(simple_command->argv);
		simple_command->argv = NULL;
		free(simple_command);
	}
	return (NULL);
}

static int		init_arguments(t_simple_cmd *simple_command, t_token **token)
{
	t_argument	*last_arg;

	last_arg = simple_command->arguments;
	if (last_arg != NULL)
	{
		while (last_arg->next != NULL)
			last_arg = last_arg->next;
		last_arg->next = parse_arguments(token);
		if (last_arg->next == NULL)
			return (-1);
	}
	else
	{
		simple_command->arguments = parse_arguments(token);
		if (simple_command->arguments == NULL)
			return (-1);
	}
	return (0);
}

static int		init_redirects(t_simple_cmd *simple_command, t_token **token)
{
	t_io_redirect	*last_redirect;

	last_redirect = simple_command->redirects;
	if (last_redirect != NULL)
	{
		while (last_redirect->next != NULL)
			last_redirect = last_redirect->next;
		last_redirect->next = parse_io_redirect(token);
		if (last_redirect->next == NULL)
			return (-1);
	}
	else
	{
		simple_command->redirects = parse_io_redirect(token);
		if (simple_command->redirects == NULL)
			return (-1);
	}
	return (0);
}

static int		init_assignments(t_simple_cmd *simple_command, t_token **token)
{
	if (is_assignment((*token)->value) == true)
	{
		simple_command->assignments = parse_assignments(token);
		if (simple_command->assignments == NULL)
			return (-1);
	}
	return (0);
}

t_simple_cmd	*parse_simple_command(t_token **token)
{
	t_simple_cmd	*simple_command;

	if (token == NULL || *token == NULL)
		return (handle_error_p(invalid_token, NULL));
	if (is_start_of_cmd(*token) != 1)
	{
		handle_error_str(parsing_error, (*token)->value);
		return (NULL);
	}
	simple_command = (t_simple_cmd *)ft_memalloc(sizeof(t_simple_cmd) * 1);
	if (simple_command == NULL)
		return (handle_error_p(malloc_error, NULL));
	if (init_assignments(simple_command, token) == -1)
		return (free_simple_command(simple_command));
	while (is_start_of_cmd(*token) == 1)
	{
		if ((*token)->type == WORD)
		{
			if (init_arguments(simple_command, token) == -1)
				return (free_simple_command(simple_command));
		}
		else if (init_redirects(simple_command, token) == -1)
			return (free_simple_command(simple_command));
	}
	return (simple_command);
}
