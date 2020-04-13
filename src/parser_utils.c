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

int	is_redirect_op(t_token *token)
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

int	is_start_of_cmd(t_token *token)
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

int	is_seperator_op(t_token *token)
{
	if (token == NULL)
	{
		return (0);
	}
	if (token->type == AMP || token->type == SEMI)
	{
		return (1);
	}
	return (0);
}
