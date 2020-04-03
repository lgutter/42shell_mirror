/* ************************************************************************** */
/*                                                                            */
/*   cetushell - 21 Shell                                 ::::::::            */
/*                                                      :+:    :+:            */
/*   By: dkroeke <dkroeke@student.codam.nl>            +:+                    */
/*       lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*                                                 #+#    #+#                 */
/*   License: GPLv3                                ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H
# include "tokenizer.h"

/*
**	checks if the passed token is a valid redirection operator.
**	arg: token: the token to be checked.
**	returns:
**	0 if the token is NOT a valid redirection operator.
**	1 if the token IS a valid redirection operator.
*/
int		is_redirect_op(t_token *token);

/*
**	checks if the passed token is a valid seperation operator.
**	arg: token: the token to be checked.
**	returns:
**	0 if the token is NOT a valid seperation operator.
**	1 if the token IS a valid seperation operator.
*/
int		is_seperator_op(t_token *token);
#endif
