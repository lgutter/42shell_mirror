/* ************************************************************************** */
/*                                                                            */
/*   cetushell - 21 Shell                                 ::::::::            */
/*                                                      :+:    :+:            */
/*   By: dkroeke <dkroeke@student.codam.nl>            +:+                    */
/*       lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*                                                  #+#    #+#                */
/*   License: GPLv3                                ########   odam.nl         */
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
