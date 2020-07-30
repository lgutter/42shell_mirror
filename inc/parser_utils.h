/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 17:35:25 by lgutter       #+#    #+#                 */
/*   Updated: 2020/02/10 16:45:21 by lgutter       ########   odam.nl         */
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
**	checks if the passed token is a valid start of a redirection.
**	arg: token: the token to be checked.
**	returns:
**	0 if the token is NOT a valid start of a redirection.
**	1 if the token IS a valid start of a redirection.
*/
int		is_start_of_redirect(t_token *token);

/*
**	checks if the passed token is a valid start of a simple command.
**	arg: token: the token to be checked.
**	returns:
**	0 if the token is NOT a valid start of a simple command.
**	1 if the token IS a valid start of a simple command.
*/
int		is_start_of_cmd(t_token *token);

/*
**	checks if the passed token is a valid seperation operator.
**	arg: token: the token to be checked.
**	returns:
**	0 if the token is NOT a valid seperation operator.
**	1 if the token IS a valid seperation operator.
*/
int		is_seperator_op(t_token *token);

/*
**	walks through the token list and builds a string for the current
**	pipe sequence, which is up until (and including) the first PIPE token.
**	every token will be seperated by a single space.
**	returns:
**		the resulting string on succes.
**		NULL on failure (malloc failure)
*/
char	*get_pipe_seq_str(t_token *token);

/*
**	walks through the token list and builds a string for the current
**	complete command, which is up until (and including) the first
**	seperator token.
**	every token will be seperated by a single space.
**	returns:
**		the resulting string on succes.
**		NULL on failure (malloc failure)
*/
char	*get_command_str(t_token *token);

/*
**	checks if the given string is a valid assignment word, meaing it contains
**	an equals sign (=), and the part before the equals sign does not contain
**	any quoting characters.
*/
bool	is_assignment(char *word);

#endif
