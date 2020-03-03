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

#ifndef TOKEN_TRANS_TABLE_H
# define TOKEN_TRANS_TABLE_H
# include "tokenizer.h"

# include <stdbool.h>

# define ADD_CHAR	true
# define SKIP_CHAR	false

typedef enum		e_type
{
	undetermined = 0,
	WORD,
	IO_NUMBER,
	NEWLINE,
	PIPE,
	SEMI,
	AMP,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	LESSAMP,
	GREATAMP
}					t_type;

typedef enum		e_state
{
	invalid = 0,
	eof,
	blank,
	state_word,
	newline,
	semicolon,
	number,
	less,
	great,
	dless,
	dgreat,
	lessamp,
	greatamp,
	pipe,
	semi,
	amp,
	start_state
}					t_state;

typedef struct		s_rules
{
	t_state			next_state;
	t_type			delimit_type;
	bool			add_char;
}					t_rules;

typedef struct		s_trans
{
	struct s_rules	rules[256];
	struct s_rules	catch_state;
}					t_trans;

static const t_trans g_token_trans[] = {
	[state_word] = {
		.rules = {
			['\0']		= {eof, WORD, SKIP_CHAR},
			[' ']		= {blank, WORD, SKIP_CHAR},
			['\t']		= {blank, WORD, SKIP_CHAR},
			['\n']		= {newline, WORD, ADD_CHAR},
			['<']		= {less, WORD, ADD_CHAR},
			['>']		= {great, WORD, ADD_CHAR},
			['&']		= {amp, WORD, ADD_CHAR},
			['|']		= {pipe, WORD, ADD_CHAR},
			[';']		= {semicolon, WORD, ADD_CHAR}
		},
		.catch_state	= {state_word, undetermined, ADD_CHAR}
	},
	[blank] =
	{
		.rules = {
			['\0']		= {eof, undetermined, SKIP_CHAR},
			[' ']		= {blank, undetermined, SKIP_CHAR},
			['\t']		= {blank, undetermined, SKIP_CHAR},
			['\n']		= {newline, undetermined, ADD_CHAR},
			['0']		= {number, undetermined, ADD_CHAR},
			['1']		= {number, undetermined, ADD_CHAR},
			['2']		= {number, undetermined, ADD_CHAR},
			['3']		= {number, undetermined, ADD_CHAR},
			['4']		= {number, undetermined, ADD_CHAR},
			['5']		= {number, undetermined, ADD_CHAR},
			['6']		= {number, undetermined, ADD_CHAR},
			['7']		= {number, undetermined, ADD_CHAR},
			['8']		= {number, undetermined, ADD_CHAR},
			['9']		= {number, undetermined, ADD_CHAR},
			['<']		= {less, undetermined, ADD_CHAR},
			['>']		= {great, undetermined, ADD_CHAR},
			['&']		= {amp, undetermined, ADD_CHAR},
			['|']		= {pipe, undetermined, ADD_CHAR},
			[';']		= {semicolon, undetermined, ADD_CHAR}
		},
		.catch_state	= {state_word, undetermined, ADD_CHAR}
	},
	[number] =
	{
		.rules = {
			['\0']		= {eof, WORD, SKIP_CHAR},
			[' ']		= {blank, WORD, SKIP_CHAR},
			['\t']		= {blank, WORD, SKIP_CHAR},
			['\n']		= {newline, WORD, ADD_CHAR},
			['0']		= {number, undetermined, ADD_CHAR},
			['1']		= {number, undetermined, ADD_CHAR},
			['2']		= {number, undetermined, ADD_CHAR},
			['3']		= {number, undetermined, ADD_CHAR},
			['4']		= {number, undetermined, ADD_CHAR},
			['5']		= {number, undetermined, ADD_CHAR},
			['6']		= {number, undetermined, ADD_CHAR},
			['7']		= {number, undetermined, ADD_CHAR},
			['8']		= {number, undetermined, ADD_CHAR},
			['9']		= {number, undetermined, ADD_CHAR},
			['<']		= {less, IO_NUMBER, ADD_CHAR},
			['>']		= {great, IO_NUMBER, ADD_CHAR},
			['&']		= {amp, WORD, ADD_CHAR},
			['|']		= {pipe, WORD, ADD_CHAR},
			[';']		= {semicolon, WORD, ADD_CHAR}
		},
		.catch_state	= {state_word, undetermined, ADD_CHAR}
	},
	[less] =
	{
		.rules = {
			['\0']		= {eof, LESS, SKIP_CHAR},
			[' ']		= {blank, LESS, SKIP_CHAR},
			['\t']		= {blank, LESS, SKIP_CHAR},
			['\n']		= {newline, LESS, ADD_CHAR},
			['0']		= {number, LESS, ADD_CHAR},
			['1']		= {number, LESS, ADD_CHAR},
			['2']		= {number, LESS, ADD_CHAR},
			['3']		= {number, LESS, ADD_CHAR},
			['4']		= {number, LESS, ADD_CHAR},
			['5']		= {number, LESS, ADD_CHAR},
			['6']		= {number, LESS, ADD_CHAR},
			['7']		= {number, LESS, ADD_CHAR},
			['8']		= {number, LESS, ADD_CHAR},
			['9']		= {number, LESS, ADD_CHAR},
			['<']		= {dless, undetermined, ADD_CHAR},
			['>']		= {great, LESS, ADD_CHAR},
			['&']		= {lessamp, undetermined, ADD_CHAR},
			['|']		= {pipe, LESS, ADD_CHAR},
			[';']		= {semicolon, LESS, ADD_CHAR}
		},
		.catch_state	= {state_word, LESS, ADD_CHAR}
	},
	[dless] =
	{
		.rules = {
			['\0']		= {eof, DLESS, SKIP_CHAR},
			[' ']		= {blank, DLESS, SKIP_CHAR},
			['\t']		= {blank, DLESS, SKIP_CHAR},
			['\n']		= {newline, DLESS, ADD_CHAR},
			['0']		= {number, DLESS, ADD_CHAR},
			['1']		= {number, DLESS, ADD_CHAR},
			['2']		= {number, DLESS, ADD_CHAR},
			['3']		= {number, DLESS, ADD_CHAR},
			['4']		= {number, DLESS, ADD_CHAR},
			['5']		= {number, DLESS, ADD_CHAR},
			['6']		= {number, DLESS, ADD_CHAR},
			['7']		= {number, DLESS, ADD_CHAR},
			['8']		= {number, DLESS, ADD_CHAR},
			['9']		= {number, DLESS, ADD_CHAR},
			['<']		= {less, DLESS, ADD_CHAR},
			['>']		= {great, DLESS, ADD_CHAR},
			['&']		= {amp, DLESS, ADD_CHAR},
			['|']		= {pipe, DLESS, ADD_CHAR},
			[';']		= {semicolon, DLESS, ADD_CHAR}
		},
		.catch_state	= {state_word, DLESS, ADD_CHAR}
	},
	[great] =
	{
		.rules = {
			['\0']		= {eof, GREAT, SKIP_CHAR},
			[' ']		= {blank, GREAT, SKIP_CHAR},
			['\t']		= {blank, GREAT, SKIP_CHAR},
			['\n']		= {newline, GREAT, ADD_CHAR},
			['0']		= {number, GREAT, ADD_CHAR},
			['1']		= {number, GREAT, ADD_CHAR},
			['2']		= {number, GREAT, ADD_CHAR},
			['3']		= {number, GREAT, ADD_CHAR},
			['4']		= {number, GREAT, ADD_CHAR},
			['5']		= {number, GREAT, ADD_CHAR},
			['6']		= {number, GREAT, ADD_CHAR},
			['7']		= {number, GREAT, ADD_CHAR},
			['8']		= {number, GREAT, ADD_CHAR},
			['9']		= {number, GREAT, ADD_CHAR},
			['<']		= {less, GREAT, ADD_CHAR},
			['>']		= {dgreat, undetermined, ADD_CHAR},
			['&']		= {greatamp, undetermined, ADD_CHAR},
			['|']		= {pipe, GREAT, ADD_CHAR},
			[';']		= {semicolon, GREAT, ADD_CHAR}
		},
		.catch_state	= {state_word, GREAT, ADD_CHAR}
	},
	[dgreat] =
	{
		.rules = {
			['\0']		= {eof, DGREAT, SKIP_CHAR},
			[' ']		= {blank, DGREAT, SKIP_CHAR},
			['\t']		= {blank, DGREAT, SKIP_CHAR},
			['\n']		= {newline, DGREAT, ADD_CHAR},
			['0']		= {number, DGREAT, ADD_CHAR},
			['1']		= {number, DGREAT, ADD_CHAR},
			['2']		= {number, DGREAT, ADD_CHAR},
			['3']		= {number, DGREAT, ADD_CHAR},
			['4']		= {number, DGREAT, ADD_CHAR},
			['5']		= {number, DGREAT, ADD_CHAR},
			['6']		= {number, DGREAT, ADD_CHAR},
			['7']		= {number, DGREAT, ADD_CHAR},
			['8']		= {number, DGREAT, ADD_CHAR},
			['9']		= {number, DGREAT, ADD_CHAR},
			['<']		= {less, DGREAT, ADD_CHAR},
			['>']		= {great, DGREAT, ADD_CHAR},
			['&']		= {amp, DGREAT, ADD_CHAR},
			['|']		= {pipe, DGREAT, ADD_CHAR},
			[';']		= {semicolon, DGREAT, ADD_CHAR}
		},
		.catch_state	= {state_word, DGREAT, ADD_CHAR}
	},
	[lessamp] =
	{
		.rules = {
			['\0']		= {eof, LESSAMP, SKIP_CHAR},
			[' ']		= {blank, LESSAMP, SKIP_CHAR},
			['\t']		= {blank, LESSAMP, SKIP_CHAR},
			['\n']		= {newline, LESSAMP, ADD_CHAR},
			['0']		= {number, LESSAMP, ADD_CHAR},
			['1']		= {number, LESSAMP, ADD_CHAR},
			['2']		= {number, LESSAMP, ADD_CHAR},
			['3']		= {number, LESSAMP, ADD_CHAR},
			['4']		= {number, LESSAMP, ADD_CHAR},
			['5']		= {number, LESSAMP, ADD_CHAR},
			['6']		= {number, LESSAMP, ADD_CHAR},
			['7']		= {number, LESSAMP, ADD_CHAR},
			['8']		= {number, LESSAMP, ADD_CHAR},
			['9']		= {number, LESSAMP, ADD_CHAR},
			['<']		= {less, LESSAMP, ADD_CHAR},
			['>']		= {great, LESSAMP, ADD_CHAR},
			['&']		= {amp, LESSAMP, ADD_CHAR},
			['|']		= {pipe, LESSAMP, ADD_CHAR},
			[';']		= {semicolon, LESSAMP, ADD_CHAR}
		},
		.catch_state	= {state_word, LESSAMP, ADD_CHAR}
	},
	[greatamp] =
	{
		.rules = {
			['\0']		= {eof, GREATAMP, SKIP_CHAR},
			[' ']		= {blank, GREATAMP, SKIP_CHAR},
			['\t']		= {blank, GREATAMP, SKIP_CHAR},
			['\n']		= {newline, GREATAMP, ADD_CHAR},
			['0']		= {number, GREATAMP, ADD_CHAR},
			['1']		= {number, GREATAMP, ADD_CHAR},
			['2']		= {number, GREATAMP, ADD_CHAR},
			['3']		= {number, GREATAMP, ADD_CHAR},
			['4']		= {number, GREATAMP, ADD_CHAR},
			['5']		= {number, GREATAMP, ADD_CHAR},
			['6']		= {number, GREATAMP, ADD_CHAR},
			['7']		= {number, GREATAMP, ADD_CHAR},
			['8']		= {number, GREATAMP, ADD_CHAR},
			['9']		= {number, GREATAMP, ADD_CHAR},
			['<']		= {less, GREATAMP, ADD_CHAR},
			['>']		= {great, GREATAMP, ADD_CHAR},
			['&']		= {amp, GREATAMP, ADD_CHAR},
			['|']		= {pipe, GREATAMP, ADD_CHAR},
			[';']		= {semicolon, GREATAMP, ADD_CHAR}
		},
		.catch_state	= {state_word, GREATAMP, ADD_CHAR}
	},
};

#endif
