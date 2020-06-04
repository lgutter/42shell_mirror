/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processing.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 15:26:18 by lgutter       #+#    #+#                 */
/*   Updated: 2020/06/04 15:26:18 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSING_H
# define PROCESSING_H
# include "cetushell.h"
# include "environment.h"

typedef enum	e_q_table
{
	ALL_QUOTES_TABLE = 0,
	HERE_END_TABLE,
	HEREDOCS_TABLE
}				t_q_table;

/*
**	performs environment expansions and quote removal on the string pointed
**	to by the argument word. The passed string should not contain unterminated
**	quotes. These can be handled beforehand with check_quote and complete_quote.
**	arguments:
**	shell:		a pointer to the shell struct.
**	word:		a pointer to the string to be processed.
**	table_type:	which transition table to use. can be ALL_QUOTES_TABLE,
**				HERE_END_TABLE or HEREDOCS_TABLE.
**	returns:
**	0 on succes.
**	-1 on failure.
*/
int				process_word(t_shell *shell, char **word, t_q_table table_type);

/*
**	performs environment expansions and quote completion + removal on all
**	relevant elements in the redirections.
**	arguments:
**	shell:		a pointer to the shell struct.
**	redirects:	a pointer to the first io_redirect struct.
**	returns:
**	0 on succes.
**	-1 on failure.
*/
int				process_redirects(t_shell *shell, t_io_redirect *redirects);

/*
**	performs environment expansions and quote removal on all
**	relevant elements in a complete_command. (arguments and redirections)
**	arguments:
**	shell:				a pointer to the shell struct.
**	complete_command:	a pointer to the first complete_command struct.
**	returns:
**	0 on succes.
**	-1 on failure.
*/
int				word_processing(t_shell *shell, t_complete_cmd *complete_cmd);

/*
**	Takes a pointer to a string and the env list,
**	and a read and write index, assuming the read index is on a dollar sign.
**	on succes, frees the old string and replaces it with the new one.
**	on failure, nothing is changed.
**	Returns:
**	- 0 on succes.
**	- errid error code on failure.
*/
int				expand_variable(t_shell *shell, char **string,
												size_t *read, size_t *write);

/*
**	Takes a pointer to a string and the env list,
**	and expands the string correctly if it starts with ~.
**	on succes, frees the old string and replaces it with the new one.
**	on failure, nothing is changed.
**	Returns:
**	- 0 on succes.
**	- errid error code on failure.
*/
int				expand_home(t_env *env_list, char **string,
												size_t *read, size_t *write);

#endif
