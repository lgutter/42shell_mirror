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

/*
**	takes the shell struct and a pointer to the input buffer, and runs it
**	through the tokenizer, parser, word processing, and the executor.
**	arguments:
**	shell:	a pointer to the shell struct. (needed for quote completion)
**	buffer: a pointer to the input string.
**	returns:
**	o on succes.
**	-1 on failure.
*/
int		handle_input(t_shell *shell, char **buffer);

/*
**	performs environment expansions and quote removal on the string pointed
**	to by the argument word. If the string contains an unterminated quote,
**	the user will be asked to complete it.
**	arguments:
**	shell:		a pointer to the shell struct. (needed for quote completion)
**	env_list:	a pointer to the first element in the environment list.
**	word:		a pointer to the string to be processed.
**	char:		if this argument == 'y', environment expansions will be done.
**	returns:
**	0 on succes.
**	-1 on failure.
*/
int		process_word(t_shell *shell, t_env *env_list, char **word, char expand);

/*
**	performs environment expansions and quote completion + removal on all
**	relevant elements in a complete_command. (arguments and redirections)
**	arguments:
**	shell:				a pointer to the shell struct. (for quote completion)
**	env_list:			a pointer to the first element in the environment list.
**	complete_command:	a pointer to the first complete_command struct.
**	returns:
**	0 on succes.
**	-1 on failure.
*/
int		word_processing(t_shell *shell, t_env *env_list,
						t_complete_cmd *complete_command);
#endif
