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
	OPERATOR,
	NEWLINE,
	SEMICOLON
}					t_type;

typedef enum		e_state
{
	invalid = 0,
	state_word,
	number,
	is_operator,
	blank,
	eof,
	newline,
	semicolon,
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
			['<']		= {is_operator, WORD, ADD_CHAR},
			['>']		= {is_operator, WORD, ADD_CHAR},
			['&']		= {is_operator, WORD, ADD_CHAR},
			['|']		= {is_operator, WORD, ADD_CHAR},
			['(']		= {is_operator, WORD, ADD_CHAR},
			[')']		= {is_operator, WORD, ADD_CHAR},
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
			['<']		= {is_operator, undetermined, ADD_CHAR},
			['>']		= {is_operator, undetermined, ADD_CHAR},
			['&']		= {is_operator, undetermined, ADD_CHAR},
			['|']		= {is_operator, undetermined, ADD_CHAR},
			['(']		= {is_operator, undetermined, ADD_CHAR},
			[')']		= {is_operator, undetermined, ADD_CHAR},
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
			['<']		= {is_operator, IO_NUMBER, ADD_CHAR},
			['>']		= {is_operator, IO_NUMBER, ADD_CHAR},
			['&']		= {is_operator, WORD, ADD_CHAR},
			['|']		= {is_operator, WORD, ADD_CHAR},
			['(']		= {is_operator, WORD, ADD_CHAR},
			[')']		= {is_operator, WORD, ADD_CHAR},
			[';']		= {semicolon, WORD, ADD_CHAR}
		},
		.catch_state	= {state_word, undetermined, ADD_CHAR}
	},
	[is_operator] =
	{
		.rules = {
			['\0']		= {eof, OPERATOR, SKIP_CHAR},
			[' ']		= {blank, OPERATOR, SKIP_CHAR},
			['\t']		= {blank, OPERATOR, SKIP_CHAR},
			['\n']		= {newline, OPERATOR, ADD_CHAR},
			['0']		= {number, OPERATOR, ADD_CHAR},
			['1']		= {number, OPERATOR, ADD_CHAR},
			['2']		= {number, OPERATOR, ADD_CHAR},
			['3']		= {number, OPERATOR, ADD_CHAR},
			['4']		= {number, OPERATOR, ADD_CHAR},
			['5']		= {number, OPERATOR, ADD_CHAR},
			['6']		= {number, OPERATOR, ADD_CHAR},
			['7']		= {number, OPERATOR, ADD_CHAR},
			['8']		= {number, OPERATOR, ADD_CHAR},
			['9']		= {number, OPERATOR, ADD_CHAR},
			['<']		= {is_operator, OPERATOR, ADD_CHAR},
			['>']		= {is_operator, OPERATOR, ADD_CHAR},
			['&']		= {is_operator, OPERATOR, ADD_CHAR},
			['|']		= {is_operator, OPERATOR, ADD_CHAR},
			['(']		= {is_operator, OPERATOR, ADD_CHAR},
			[')']		= {is_operator, OPERATOR, ADD_CHAR},
			[';']		= {semicolon, OPERATOR, ADD_CHAR}
		},
		.catch_state	= {state_word, OPERATOR, ADD_CHAR}
	},
};

#endif
