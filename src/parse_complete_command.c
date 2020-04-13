/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_complete_cmd.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/06 17:03:13 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"

t_complete_cmd			*free_complete_command(t_complete_cmd *complete_cmd)
{
	if (complete_cmd == NULL)
		return (NULL);
	complete_cmd->seperator_op = no_seperator_op;
	free_pipe_sequence(complete_cmd->pipe_sequence);
	complete_cmd->pipe_sequence = NULL;
	complete_cmd->next = free_complete_command(complete_cmd->next);
	free(complete_cmd);
	return (NULL);
}

static t_complete_cmd	*init_complete_command(t_token **token)
{
	t_complete_cmd *complete_cmd;

	complete_cmd = (t_complete_cmd *)ft_memalloc(sizeof(t_complete_cmd) * 1);
	if (complete_cmd == NULL)
	{
		handle_error(malloc_error);
		return (NULL);
	}
	complete_cmd->pipe_sequence = parse_pipe_sequence(token);
	if (complete_cmd->pipe_sequence == NULL)
	{
		complete_cmd = free_complete_command(complete_cmd);
		return (NULL);
	}
	if (*token != NULL && is_seperator_op(*token))
	{
		complete_cmd->seperator_op = (t_seperator_op)(*token)->type;
		*token = (*token)->next;
	}
	else
		complete_cmd->seperator_op = no_seperator_op;
	complete_cmd->next = NULL;
	return (complete_cmd);
}

t_complete_cmd			*parse_complete_command(t_token **token)
{
	t_complete_cmd	*complete_cmd;

	if (token == NULL || *token == NULL || is_start_of_cmd(*token) != 1)
	{
		handle_error_str(parsing_error, (*token)->value);
		return (NULL);
	}
	complete_cmd = init_complete_command(token);
	if (complete_cmd == NULL)
		return (NULL);
	if (*token != NULL)
	{
		complete_cmd->next = parse_complete_command(token);
		if (complete_cmd->next == NULL)
			return (free_complete_command(complete_cmd));
	}
	return (complete_cmd);
}
