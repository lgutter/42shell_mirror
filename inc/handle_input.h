/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_input.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:52:43 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/14 11:52:43 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_INPUT_H
# define HANDLE_INPUT_H
# include "tokenizer.h"
# include "parser.h"
# include "environment.h"
# include "utils.h"
# include "input_control.h"
# include "cetushell.h"
# include "executor.h"

/*
**	takes the shell struct and a pointer to the input buffer, and runs it
**	through the tokenizer, parser, word processing, and the executor.
**	arguments:
**	shell:	a pointer to the shell struct. (needed for quote completion)
**	buffer: a pointer to the input string.
**	env:	the first element in the environment list.
**	returns:
**	o on succes.
**	-1 on failure.
*/
int		handle_input(t_shell *shell, char **buffer, t_env *env);

#endif
