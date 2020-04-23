/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_trans_table.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/22 11:30:43 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/22 11:52:43 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_TRANS_TABLE_H
# define QUOTE_TRANS_TABLE_H

/*
**	enumerations used to specify what do to with the current character.
**	SKIP_CHAR means the character will be discarded,
**	ADD_CHAR means it will be added to the buffer.
*/
typedef enum		e_q_action
{
	SKIP_CHAR = 0,
	ADD_CHAR
}					t_q_action;

/*
**	enumerations for all possible quoting states.
**	these are used to provide the context of characters,
**	so we can correctly determine what to do.
*/
typedef enum		e_q_state
{
	invalid = 0,
	eof,
	no_quote,
	squote,
	dquote,
	backslash,
	dq_backslash
}					t_q_state;

/*
**	the three rules we need to handle every state correctly.
**	next_state:		the next state to go to after updating the buffer.
**	add_char:		if true, the character will be added to the buffer.
*/
typedef struct		s_q_rules
{
	t_q_state		next_state;
	t_q_action		add_char;
}					t_q_rules;

/*
**	The transition struct containing all rule sets.
**	The rules array is used with the current character as index.
**	If the current character does not have a definition in the rules array,
**	we will use the catch_state instead.
*/
typedef struct		s_q_trans
{
	struct s_q_rules	rules[256];
	struct s_q_rules	catch_state;
}					t_q_trans;

/*
**	The transition table containing all the rule sets for every expected state
**	and character, + definitions of the catch state.
**	This table is structured as follows:
**	table[]{
**	- - [STATE]{
**	- - - - .rules[256] = {
**	- - - - - - [input char] = {next_state, add_char},
**	- - - - - - ...
**	- - - - },
**	- - - - .catch_state = {next_state, add_char}
**	- - },
**	- - ...
**	}
*/
static const t_q_trans g_quote_trans[] = {
	[no_quote] =
	{
		.rules = {
			['\0']		= {eof, ADD_CHAR},
			['\'']		= {squote, SKIP_CHAR},
			['"']		= {dquote, SKIP_CHAR},
			['\\']		= {backslash, SKIP_CHAR}
		},
		.catch_state	= {no_quote, ADD_CHAR}
	},
	[squote] =
	{
		.rules = {
			['\0']		= {eof, ADD_CHAR},
			['\'']		= {no_quote, SKIP_CHAR}
		},
		.catch_state	= {squote, ADD_CHAR}
	},
	[dquote] =
	{
		.rules = {
			['\0']		= {eof, ADD_CHAR},
			['"']		= {no_quote, SKIP_CHAR},
			['\\']		= {dq_backslash, SKIP_CHAR}
		},
		.catch_state	= {dquote, ADD_CHAR}
	},
	[backslash] =
	{
		.rules = {
			['\0']		= {eof, ADD_CHAR},
		},
		.catch_state	= {no_quote, ADD_CHAR}
	},
	[dq_backslash] =
	{
		.rules = {
			['\0']		= {eof, ADD_CHAR},
		},
		.catch_state	= {dquote, ADD_CHAR}
	}
};

#endif
