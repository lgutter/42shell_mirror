/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_pipe_sequence.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/06 17:03:13 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"

t_pipe_sequence			*free_pipe_sequence(t_pipe_sequence *pipe_sequence)
{
	if (pipe_sequence == NULL)
		return (NULL);
	pipe_sequence->pipe = no_pipe;
	free_simple_command(pipe_sequence->simple_command);
	pipe_sequence->simple_command = NULL;
	pipe_sequence->next = free_pipe_sequence(pipe_sequence->next);
	free(pipe_sequence);
	return (NULL);
}

static t_pipe_sequence	*init_pipe_sequence(t_token **token)
{
	t_pipe_sequence *pipe_sequence;

	pipe_sequence = (t_pipe_sequence *)ft_memalloc(sizeof(t_pipe_sequence) * 1);
	if (pipe_sequence == NULL)
	{
		handle_error(malloc_error);
		return (NULL);
	}
	pipe_sequence->simple_command = parse_simple_command(token);
	if (pipe_sequence->simple_command == NULL)
	{
		pipe_sequence = free_pipe_sequence(pipe_sequence);
		return (NULL);
	}
	if (*token != NULL && (*token)->type == PIPE)
	{
		pipe_sequence->pipe = pipe_op;
		*token = (*token)->next;
	}
	else
		pipe_sequence->pipe = no_pipe;
	pipe_sequence->next = NULL;
	return (pipe_sequence);
}

t_pipe_sequence			*parse_pipe_sequence(t_token **token)
{
	t_pipe_sequence	*pipe_sequence;

	if (token == NULL || *token == NULL)
		return (handle_error_p(invalid_token, NULL));
	if (is_start_of_cmd(*token) != 1)
	{
		handle_error_str(parsing_error, (*token)->value);
		return (NULL);
	}
	pipe_sequence = init_pipe_sequence(token);
	if (pipe_sequence == NULL)
		return (NULL);
	if (*token != NULL && is_start_of_cmd(*token) == 1)
	{
		pipe_sequence->next = parse_pipe_sequence(token);
		if (pipe_sequence->next == NULL)
		{
			free_pipe_sequence(pipe_sequence);
			return (NULL);
		}
	}
	return (pipe_sequence);
}
