/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/09 13:52:42 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/09 13:52:42 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"

int		is_redirect_op(t_token *token)
{
	if (token == NULL)
	{
		return (0);
	}
	if (token->type == LESS ||
		token->type == GREAT ||
		token->type == DGREAT ||
		token->type == LESSAMP ||
		token->type == GREATAMP)
	{
		return (1);
	}
	return (0);
}

int		is_start_of_redirect(t_token *token)
{
	if (token == NULL)
	{
		return (0);
	}
	if (token->type == LESS ||
		token->type == DLESS ||
		token->type == GREAT ||
		token->type == DGREAT ||
		token->type == LESSAMP ||
		token->type == GREATAMP ||
		token->type == IO_NUMBER)
	{
		return (1);
	}
	return (0);
}

int		is_start_of_cmd(t_token *token)
{
	if (token == NULL)
	{
		return (0);
	}
	if (token->type == LESS ||
		token->type == DLESS ||
		token->type == GREAT ||
		token->type == DGREAT ||
		token->type == LESSAMP ||
		token->type == GREATAMP ||
		token->type == IO_NUMBER ||
		token->type == WORD)
	{
		return (1);
	}
	return (0);
}

int		is_seperator_op(t_token *token)
{
	if (token == NULL)
	{
		return (0);
	}
	if (token->type == AMP || token->type == SEMI || token->type == NEWLINE ||
		token->type == ANDAND || token->type == OROR)
	{
		return (1);
	}
	return (0);
}

bool	is_assignment(char *word)
{
	size_t i;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '"' || word[i] == '\'' || word[i] == '\\')
			return (false);
		if (word[i] == '=')
			return (true);
		i++;
	}
	return (false);
}
