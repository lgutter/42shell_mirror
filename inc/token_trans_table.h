/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_trans_table.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:52:43 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/14 11:52:43 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_TRANS_TABLE_H
# define TOKEN_TRANS_TABLE_H

/*
**	enumerations used to specify what do to with the current character.
**	SKIP_CHAR means the character will be discarded,
**	ADD_CHAR_PRE means it will be added to the buffer BEFORE delimiting a token,
**	ADD_CHAR_POST will add the character to the buffer AFTER delimiting a token.
*/
typedef enum		e_action
{
	SKIP_CHAR = 0,
	ADD_CHAR_PRE,
	ADD_CHAR_POST
}					t_action;

/*
**	enumerations for all the possible token types.
*/
typedef enum		e_type
{
	undetermined = 0,
	WORD,
	IO_NUMBER,
	NEWLINE,
	PIPE,
	SEMI,
	AMP,
	ANDAND,
	OROR,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	LESSAMP,
	GREATAMP
}					t_type;

/*
**	enumerations for all possible states in the tokenizer.
**	these are used to provide the context of characters,
**	so we can correctly determine the type of a token.
**
** substitution is a magic state where another lexer is spawned to find
** the end of the $(). It will add everything up to and including the closing
** ')' and return to state_word without delimiting.
**
** dq_substitution is the same as substitution but returns to dquote instead.
*/
typedef enum		e_state
{
	invalid = 0,
	eof,
	blank,
	state_word,
	number,
	less,
	great,
	pipe_state,
	pipe_blank,
	pre_unt_pipe,
	unt_pipe,
	amp,
	state_newline,
	semicolon,
	squote,
	unt_squote,
	dquote,
	unt_dquote,
	backslash,
	unt_backslash,
	dq_backslash,
	comment,
	pipe_comment,
	dollar,
	dq_dollar,
	substitution,
	dq_substitution
}					t_state;

/*
**	the three rules we need to handle every state correctly.
**	next_state:		the next state to go to after delimiting and updating buffer
**	delimit_type:	if not 0, the current buffer will be delimited and a
**					token is added to the token list.
**	add_char:		if true, the character will be added to the buffer.
**					if a token is delimited, the character is added to the
**					buffer after the current token is delimited.
*/
typedef struct		s_rules
{
	t_state			next_state;
	t_type			delimit_type;
	t_action		add_char;
}					t_rules;

/*
**	The transition struct containing all rule sets.
**	The rules array is used with the current character as index.
**	If the current character does not have a definition in the rules array,
**	we will use the catch_state instead.
*/
typedef struct		s_trans
{
	struct s_rules	rules[256];
	struct s_rules	catch_state;
}					t_trans;

/*
**	The transition table containing all the rule sets for every expected state
**	and character, + definitions of the catch state.
**	This table is structured as follows:
**	table[]{
**	- - [STATE]{
**	- - - - .rules[256] = {
**	- - - - - - [input char] = {next_state, delimit_type, add_char},
**	- - - - - - ...
**	- - - - },
**	- - - - .catch_state = {next_state, delimit_type, add_char}
**	- - },
**	- - ...
**	}
*/
static const t_trans g_token_trans[] = {
	[blank] =
	{
		.rules = {
			['\0']		= {eof, undetermined, SKIP_CHAR},
			[' ']		= {blank, undetermined, SKIP_CHAR},
			['\t']		= {blank, undetermined, SKIP_CHAR},
			['#']		= {comment, undetermined, SKIP_CHAR},
			['\n']		= {state_newline, undetermined, ADD_CHAR_POST},
			['0']		= {number, undetermined, ADD_CHAR_POST},
			['1']		= {number, undetermined, ADD_CHAR_POST},
			['2']		= {number, undetermined, ADD_CHAR_POST},
			['3']		= {number, undetermined, ADD_CHAR_POST},
			['4']		= {number, undetermined, ADD_CHAR_POST},
			['5']		= {number, undetermined, ADD_CHAR_POST},
			['6']		= {number, undetermined, ADD_CHAR_POST},
			['7']		= {number, undetermined, ADD_CHAR_POST},
			['8']		= {number, undetermined, ADD_CHAR_POST},
			['9']		= {number, undetermined, ADD_CHAR_POST},
			['<']		= {less, undetermined, ADD_CHAR_POST},
			['>']		= {great, undetermined, ADD_CHAR_POST},
			['&']		= {amp, undetermined, ADD_CHAR_POST},
			['|']		= {pipe_state, undetermined, ADD_CHAR_POST},
			[';']		= {semicolon, undetermined, ADD_CHAR_POST},
			['$']		= {dollar, undetermined, ADD_CHAR_POST},
			['\\']		= {backslash, undetermined, ADD_CHAR_POST},
			['\'']		= {squote, undetermined, ADD_CHAR_POST},
			['"']		= {dquote, undetermined, ADD_CHAR_POST}
		},
		.catch_state	= {state_word, undetermined, ADD_CHAR_POST}
	},
	[state_word] = {
		.rules = {
			['\0']		= {eof, WORD, SKIP_CHAR},
			[' ']		= {blank, WORD, SKIP_CHAR},
			['\t']		= {blank, WORD, SKIP_CHAR},
			['#']		= {comment, WORD, SKIP_CHAR},
			['\n']		= {state_newline, WORD, ADD_CHAR_POST},
			['<']		= {less, WORD, ADD_CHAR_POST},
			['>']		= {great, WORD, ADD_CHAR_POST},
			['&']		= {amp, WORD, ADD_CHAR_POST},
			['|']		= {pipe_state, WORD, ADD_CHAR_POST},
			[';']		= {semicolon, WORD, ADD_CHAR_POST},
			['$']		= {dollar, undetermined, ADD_CHAR_POST},
			['\\']		= {backslash, undetermined, ADD_CHAR_POST},
			['\'']		= {squote, undetermined, ADD_CHAR_POST},
			['"']		= {dquote, undetermined, ADD_CHAR_POST}
		},
		.catch_state	= {state_word, undetermined, ADD_CHAR_POST}
	},
	[dollar] =
	{
		.rules = {
			['\0']		= {eof, WORD, SKIP_CHAR},
			[' ']		= {blank, WORD, SKIP_CHAR},
			['\t']		= {blank, WORD, SKIP_CHAR},
			['#']		= {comment, WORD, SKIP_CHAR},
			['\n']		= {state_newline, WORD, ADD_CHAR_POST},
			['<']		= {less, WORD, ADD_CHAR_POST},
			['>']		= {great, WORD, ADD_CHAR_POST},
			['&']		= {amp, WORD, ADD_CHAR_POST},
			['|']		= {pipe_state, WORD, ADD_CHAR_POST},
			[';']		= {semicolon, WORD, ADD_CHAR_POST},
			['$']		= {dollar, undetermined, ADD_CHAR_POST},
			['\\']		= {backslash, undetermined, ADD_CHAR_POST},
			['\'']		= {squote, undetermined, ADD_CHAR_POST},
			['"']		= {dquote, undetermined, ADD_CHAR_POST},
			['(']		= {substitution, undetermined, ADD_CHAR_POST}
		},
		.catch_state = {state_word, undetermined, ADD_CHAR_POST}
	},
	[number] =
	{
		.rules = {
			['\0']		= {eof, WORD, SKIP_CHAR},
			[' ']		= {blank, WORD, SKIP_CHAR},
			['\t']		= {blank, WORD, SKIP_CHAR},
			['#']		= {comment, WORD, SKIP_CHAR},
			['\n']		= {state_newline, WORD, ADD_CHAR_POST},
			['0']		= {number, undetermined, ADD_CHAR_POST},
			['1']		= {number, undetermined, ADD_CHAR_POST},
			['2']		= {number, undetermined, ADD_CHAR_POST},
			['3']		= {number, undetermined, ADD_CHAR_POST},
			['4']		= {number, undetermined, ADD_CHAR_POST},
			['5']		= {number, undetermined, ADD_CHAR_POST},
			['6']		= {number, undetermined, ADD_CHAR_POST},
			['7']		= {number, undetermined, ADD_CHAR_POST},
			['8']		= {number, undetermined, ADD_CHAR_POST},
			['9']		= {number, undetermined, ADD_CHAR_POST},
			['<']		= {less, IO_NUMBER, ADD_CHAR_POST},
			['>']		= {great, IO_NUMBER, ADD_CHAR_POST},
			['&']		= {amp, WORD, ADD_CHAR_POST},
			['|']		= {pipe_state, WORD, ADD_CHAR_POST},
			[';']		= {semicolon, WORD, ADD_CHAR_POST},
			['$']		= {dollar, undetermined, ADD_CHAR_POST},
			['\\']		= {backslash, undetermined, ADD_CHAR_POST},
			['\'']		= {squote, undetermined, ADD_CHAR_POST},
			['"']		= {dquote, undetermined, ADD_CHAR_POST}
		},
		.catch_state	= {state_word, undetermined, ADD_CHAR_POST}
	},
	[less] =
	{
		.rules = {
			['\0']		= {eof, LESS, SKIP_CHAR},
			[' ']		= {blank, LESS, SKIP_CHAR},
			['\t']		= {blank, LESS, SKIP_CHAR},
			['#']		= {comment, LESS, SKIP_CHAR},
			['\n']		= {state_newline, LESS, ADD_CHAR_POST},
			['0']		= {number, LESS, ADD_CHAR_POST},
			['1']		= {number, LESS, ADD_CHAR_POST},
			['2']		= {number, LESS, ADD_CHAR_POST},
			['3']		= {number, LESS, ADD_CHAR_POST},
			['4']		= {number, LESS, ADD_CHAR_POST},
			['5']		= {number, LESS, ADD_CHAR_POST},
			['6']		= {number, LESS, ADD_CHAR_POST},
			['7']		= {number, LESS, ADD_CHAR_POST},
			['8']		= {number, LESS, ADD_CHAR_POST},
			['9']		= {number, LESS, ADD_CHAR_POST},
			['<']		= {blank, DLESS, ADD_CHAR_PRE},
			['>']		= {great, LESS, ADD_CHAR_POST},
			['&']		= {blank, LESSAMP, ADD_CHAR_PRE},
			['|']		= {pipe_state, LESS, ADD_CHAR_POST},
			[';']		= {semicolon, LESS, ADD_CHAR_POST},
			['$']		= {dollar, LESS, ADD_CHAR_POST},
			['\\']		= {backslash, LESS, ADD_CHAR_POST},
			['\'']		= {squote, LESS, ADD_CHAR_POST},
			['"']		= {dquote, LESS, ADD_CHAR_POST}
		},
		.catch_state	= {state_word, LESS, ADD_CHAR_POST}
	},
	[great] =
	{
		.rules = {
			['\0']		= {eof, GREAT, SKIP_CHAR},
			[' ']		= {blank, GREAT, SKIP_CHAR},
			['\t']		= {blank, GREAT, SKIP_CHAR},
			['#']		= {comment, GREAT, SKIP_CHAR},
			['\n']		= {state_newline, GREAT, ADD_CHAR_POST},
			['0']		= {number, GREAT, ADD_CHAR_POST},
			['1']		= {number, GREAT, ADD_CHAR_POST},
			['2']		= {number, GREAT, ADD_CHAR_POST},
			['3']		= {number, GREAT, ADD_CHAR_POST},
			['4']		= {number, GREAT, ADD_CHAR_POST},
			['5']		= {number, GREAT, ADD_CHAR_POST},
			['6']		= {number, GREAT, ADD_CHAR_POST},
			['7']		= {number, GREAT, ADD_CHAR_POST},
			['8']		= {number, GREAT, ADD_CHAR_POST},
			['9']		= {number, GREAT, ADD_CHAR_POST},
			['<']		= {less, GREAT, ADD_CHAR_POST},
			['>']		= {blank, DGREAT, ADD_CHAR_PRE},
			['&']		= {blank, GREATAMP, ADD_CHAR_PRE},
			['|']		= {pipe_state, GREAT, ADD_CHAR_POST},
			[';']		= {semicolon, GREAT, ADD_CHAR_POST},
			['$']		= {dollar, GREAT, ADD_CHAR_POST},
			['\\']		= {backslash, GREAT, ADD_CHAR_POST},
			['\'']		= {squote, GREAT, ADD_CHAR_POST},
			['"']		= {dquote, GREAT, ADD_CHAR_POST}
		},
		.catch_state	= {state_word, GREAT, ADD_CHAR_POST}
	},
	[pipe_state] =
	{
		.rules = {
			['\0']		= {pre_unt_pipe, PIPE, SKIP_CHAR},
			[' ']		= {pipe_blank, PIPE, SKIP_CHAR},
			['\t']		= {pipe_blank, PIPE, SKIP_CHAR},
			['#']		= {pipe_comment, PIPE, SKIP_CHAR},
			['\n']		= {pipe_blank, PIPE, SKIP_CHAR},
			['0']		= {number, PIPE, ADD_CHAR_POST},
			['1']		= {number, PIPE, ADD_CHAR_POST},
			['2']		= {number, PIPE, ADD_CHAR_POST},
			['3']		= {number, PIPE, ADD_CHAR_POST},
			['4']		= {number, PIPE, ADD_CHAR_POST},
			['5']		= {number, PIPE, ADD_CHAR_POST},
			['6']		= {number, PIPE, ADD_CHAR_POST},
			['7']		= {number, PIPE, ADD_CHAR_POST},
			['8']		= {number, PIPE, ADD_CHAR_POST},
			['9']		= {number, PIPE, ADD_CHAR_POST},
			['<']		= {less, PIPE, ADD_CHAR_POST},
			['>']		= {great, PIPE, ADD_CHAR_POST},
			['&']		= {amp, PIPE, ADD_CHAR_POST},
			['|']		= {blank, OROR, ADD_CHAR_PRE},
			[';']		= {semicolon, PIPE, ADD_CHAR_POST},
			['$']		= {dollar, PIPE, ADD_CHAR_POST},
			['\\']		= {backslash, PIPE, ADD_CHAR_POST},
			['\'']		= {squote, PIPE, ADD_CHAR_POST},
			['"']		= {dquote, PIPE, ADD_CHAR_POST}
		},
		.catch_state	= {state_word, PIPE, ADD_CHAR_POST}
	},
	[pipe_blank] =
	{
		.rules = {
			['\0']		= {unt_pipe, undetermined, SKIP_CHAR},
			[' ']		= {pipe_blank, undetermined, SKIP_CHAR},
			['\t']		= {pipe_blank, undetermined, SKIP_CHAR},
			['#']		= {pipe_comment, undetermined, SKIP_CHAR},
			['\n']		= {pipe_blank, undetermined, SKIP_CHAR},
			['0']		= {number, undetermined, ADD_CHAR_POST},
			['1']		= {number, undetermined, ADD_CHAR_POST},
			['2']		= {number, undetermined, ADD_CHAR_POST},
			['3']		= {number, undetermined, ADD_CHAR_POST},
			['4']		= {number, undetermined, ADD_CHAR_POST},
			['5']		= {number, undetermined, ADD_CHAR_POST},
			['6']		= {number, undetermined, ADD_CHAR_POST},
			['7']		= {number, undetermined, ADD_CHAR_POST},
			['8']		= {number, undetermined, ADD_CHAR_POST},
			['9']		= {number, undetermined, ADD_CHAR_POST},
			['<']		= {less, undetermined, ADD_CHAR_POST},
			['>']		= {great, undetermined, ADD_CHAR_POST},
			['&']		= {amp, undetermined, ADD_CHAR_POST},
			['|']		= {pipe_state, undetermined, ADD_CHAR_POST},
			[';']		= {semicolon, undetermined, ADD_CHAR_POST},
			['$']		= {dollar, undetermined, ADD_CHAR_POST},
			['\\']		= {backslash, undetermined, ADD_CHAR_POST},
			['\'']		= {squote, undetermined, ADD_CHAR_POST},
			['"']		= {dquote, undetermined, ADD_CHAR_POST}
		},
		.catch_state	= {state_word, undetermined, ADD_CHAR_POST}
	},
	[pre_unt_pipe] =
	{
		.rules = {
			['\0']		= {unt_pipe, undetermined, SKIP_CHAR},
		},
		.catch_state	= {unt_pipe, undetermined, SKIP_CHAR}
	},
	[unt_pipe] =
	{
		.rules = {
			['\0']		= {unt_pipe, undetermined, SKIP_CHAR},
			[' ']		= {pipe_blank, undetermined, SKIP_CHAR},
			['\t']		= {pipe_blank, undetermined, SKIP_CHAR},
			['\n']		= {pipe_blank, undetermined, SKIP_CHAR},
			['#']		= {pipe_comment, undetermined, SKIP_CHAR},
			['0']		= {number, undetermined, ADD_CHAR_POST},
			['1']		= {number, undetermined, ADD_CHAR_POST},
			['2']		= {number, undetermined, ADD_CHAR_POST},
			['3']		= {number, undetermined, ADD_CHAR_POST},
			['4']		= {number, undetermined, ADD_CHAR_POST},
			['5']		= {number, undetermined, ADD_CHAR_POST},
			['6']		= {number, undetermined, ADD_CHAR_POST},
			['7']		= {number, undetermined, ADD_CHAR_POST},
			['8']		= {number, undetermined, ADD_CHAR_POST},
			['9']		= {number, undetermined, ADD_CHAR_POST},
			['<']		= {less, undetermined, ADD_CHAR_POST},
			['>']		= {great, undetermined, ADD_CHAR_POST},
			['&']		= {amp, undetermined, ADD_CHAR_POST},
			['|']		= {pipe_state, undetermined, ADD_CHAR_POST},
			[';']		= {semicolon, undetermined, ADD_CHAR_POST},
			['$']		= {dollar, undetermined, ADD_CHAR_POST},
			['\\']		= {backslash, undetermined, ADD_CHAR_POST},
			['\'']		= {squote, undetermined, ADD_CHAR_POST},
			['"']		= {dquote, undetermined, ADD_CHAR_POST}
		},
		.catch_state	= {state_word, undetermined, ADD_CHAR_POST}
	},
	[amp] =
	{
		.rules = {
			['\0']		= {eof, AMP, SKIP_CHAR},
			[' ']		= {blank, AMP, SKIP_CHAR},
			['\t']		= {blank, AMP, SKIP_CHAR},
			['#']		= {comment, AMP, SKIP_CHAR},
			['\n']		= {state_newline, AMP, ADD_CHAR_POST},
			['0']		= {number, AMP, ADD_CHAR_POST},
			['1']		= {number, AMP, ADD_CHAR_POST},
			['2']		= {number, AMP, ADD_CHAR_POST},
			['3']		= {number, AMP, ADD_CHAR_POST},
			['4']		= {number, AMP, ADD_CHAR_POST},
			['5']		= {number, AMP, ADD_CHAR_POST},
			['6']		= {number, AMP, ADD_CHAR_POST},
			['7']		= {number, AMP, ADD_CHAR_POST},
			['8']		= {number, AMP, ADD_CHAR_POST},
			['9']		= {number, AMP, ADD_CHAR_POST},
			['<']		= {less, AMP, ADD_CHAR_POST},
			['>']		= {great, AMP, ADD_CHAR_POST},
			['&']		= {blank, ANDAND, ADD_CHAR_PRE},
			['|']		= {pipe_state, AMP, ADD_CHAR_POST},
			[';']		= {semicolon, AMP, ADD_CHAR_POST},
			['$']		= {dollar, AMP, ADD_CHAR_POST},
			['\\']		= {backslash, AMP, ADD_CHAR_POST},
			['\'']		= {squote, AMP, ADD_CHAR_POST},
			['"']		= {dquote, AMP, ADD_CHAR_POST}
		},
		.catch_state	= {state_word, AMP, ADD_CHAR_POST}
	},
	[state_newline] =
	{
		.rules = {
			['\0']		= {eof, NEWLINE, SKIP_CHAR},
			[' ']		= {blank, NEWLINE, SKIP_CHAR},
			['\t']		= {blank, NEWLINE, SKIP_CHAR},
			['#']		= {comment, NEWLINE, SKIP_CHAR},
			['\n']		= {state_newline, NEWLINE, ADD_CHAR_POST},
			['0']		= {number, NEWLINE, ADD_CHAR_POST},
			['1']		= {number, NEWLINE, ADD_CHAR_POST},
			['2']		= {number, NEWLINE, ADD_CHAR_POST},
			['3']		= {number, NEWLINE, ADD_CHAR_POST},
			['4']		= {number, NEWLINE, ADD_CHAR_POST},
			['5']		= {number, NEWLINE, ADD_CHAR_POST},
			['6']		= {number, NEWLINE, ADD_CHAR_POST},
			['7']		= {number, NEWLINE, ADD_CHAR_POST},
			['8']		= {number, NEWLINE, ADD_CHAR_POST},
			['9']		= {number, NEWLINE, ADD_CHAR_POST},
			['<']		= {less, NEWLINE, ADD_CHAR_POST},
			['>']		= {great, NEWLINE, ADD_CHAR_POST},
			['&']		= {amp, NEWLINE, ADD_CHAR_POST},
			['|']		= {pipe_state, NEWLINE, ADD_CHAR_POST},
			[';']		= {semicolon, NEWLINE, ADD_CHAR_POST},
			['$']		= {dollar, NEWLINE, ADD_CHAR_POST},
			['\\']		= {backslash, NEWLINE, ADD_CHAR_POST},
			['\'']		= {squote, NEWLINE, ADD_CHAR_POST},
			['"']		= {dquote, NEWLINE, ADD_CHAR_POST}
		},
		.catch_state	= {state_word, NEWLINE, ADD_CHAR_POST}
	},
	[semicolon] =
	{
		.rules = {
			['\0']		= {eof, SEMI, SKIP_CHAR},
			[' ']		= {blank, SEMI, SKIP_CHAR},
			['\t']		= {blank, SEMI, SKIP_CHAR},
			['#']		= {comment, SEMI, SKIP_CHAR},
			['\n']		= {state_newline, SEMI, ADD_CHAR_POST},
			['0']		= {number, SEMI, ADD_CHAR_POST},
			['1']		= {number, SEMI, ADD_CHAR_POST},
			['2']		= {number, SEMI, ADD_CHAR_POST},
			['3']		= {number, SEMI, ADD_CHAR_POST},
			['4']		= {number, SEMI, ADD_CHAR_POST},
			['5']		= {number, SEMI, ADD_CHAR_POST},
			['6']		= {number, SEMI, ADD_CHAR_POST},
			['7']		= {number, SEMI, ADD_CHAR_POST},
			['8']		= {number, SEMI, ADD_CHAR_POST},
			['9']		= {number, SEMI, ADD_CHAR_POST},
			['<']		= {less, SEMI, ADD_CHAR_POST},
			['>']		= {great, SEMI, ADD_CHAR_POST},
			['&']		= {amp, SEMI, ADD_CHAR_POST},
			['|']		= {pipe_state, SEMI, ADD_CHAR_POST},
			[';']		= {semicolon, SEMI, ADD_CHAR_POST},
			['$']		= {dollar, SEMI, ADD_CHAR_POST},
			['\\']		= {backslash, SEMI, ADD_CHAR_POST},
			['\'']		= {squote, SEMI, ADD_CHAR_POST},
			['"']		= {dquote, SEMI, ADD_CHAR_POST}
		},
		.catch_state	= {state_word, SEMI, ADD_CHAR_POST}
	},
	[squote] =
	{
		.rules = {
			['\0']		= {unt_squote, undetermined, ADD_CHAR_POST},
			['\'']		= {state_word, undetermined, ADD_CHAR_POST}
		},
		.catch_state	= {squote, undetermined, ADD_CHAR_POST}
	},
	[unt_squote] =
	{
		.rules = {
			['\0']		= {unt_squote, undetermined, ADD_CHAR_POST},
			['\'']		= {state_word, undetermined, ADD_CHAR_POST}
		},
		.catch_state	= {squote, undetermined, ADD_CHAR_POST}
	},
	[dquote] =
	{
		.rules = {
			['\0']		= {unt_dquote, undetermined, ADD_CHAR_POST},
			['$']		= {dq_dollar, undetermined, ADD_CHAR_POST},
			['"']		= {state_word, undetermined, ADD_CHAR_POST},
			['\\']		= {dq_backslash, undetermined, ADD_CHAR_POST}
		},
		.catch_state	= {dquote, undetermined, ADD_CHAR_POST}
	},
	[unt_dquote] =
	{
		.rules = {
			['\0']		= {unt_dquote, undetermined, ADD_CHAR_POST},
			['$']		= {dq_dollar, undetermined, ADD_CHAR_POST},
			['"']		= {state_word, undetermined, ADD_CHAR_POST},
			['\\']		= {dq_backslash, undetermined, ADD_CHAR_POST}
		},
		.catch_state	= {dquote, undetermined, ADD_CHAR_POST}
	},
	[unt_backslash] =
	{
		.rules = {
			['\0']		= {unt_backslash, undetermined, ADD_CHAR_POST},
		},
		.catch_state	= {state_word, undetermined, ADD_CHAR_POST}
	},
	[dq_dollar] =
	{
		.rules = {
			['\0']		= {unt_dquote, undetermined, ADD_CHAR_POST},
			['$']		= {dq_dollar, undetermined, ADD_CHAR_POST},
			['"']		= {state_word, undetermined, ADD_CHAR_POST},
			['\\']		= {dq_backslash, undetermined, ADD_CHAR_POST},
			['(']		= {dq_substitution, undetermined, ADD_CHAR_POST}
		},
		.catch_state	= {dquote, undetermined, ADD_CHAR_POST}
	},
	[backslash] =
	{
		.rules = {
			['\0']		= {unt_backslash, undetermined, ADD_CHAR_POST},
		},
		.catch_state	= {state_word, undetermined, ADD_CHAR_POST}
	},
	[dq_backslash] =
	{
		.rules = {
			['\0']		= {unt_dquote, undetermined, ADD_CHAR_POST},
		},
		.catch_state	= {dquote, undetermined, ADD_CHAR_POST}
	},
	[comment] =
	{
		.rules = {
			['\0']		= {eof, undetermined, SKIP_CHAR},
			['\n']		= {state_newline, undetermined, SKIP_CHAR}
		},
		.catch_state	= {comment, undetermined, SKIP_CHAR}
	},
	[pipe_comment] =
	{
		.rules = {
			['\0']		= {unt_pipe, undetermined, SKIP_CHAR},
			['\n']		= {pipe_blank, undetermined, SKIP_CHAR}
		},
		.catch_state	= {pipe_comment, undetermined, SKIP_CHAR}
	},
};

#endif
