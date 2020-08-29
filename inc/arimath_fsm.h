/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arithmatic_expansion.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 10:58:15 by aholster      #+#    #+#                 */
/*   Updated: 2020/04/20 10:58:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARIMATH_FSM_H
# define ARIMATH_FSM_H

enum	e_ari_state{
	invalid_state,
	st_assert_operator,
	st_operator,
	st_encounterer,
	st_variable,
	st_number,
	st_end,
};

struct	s_ari_fsm_rule{
	enum e_ari_state	next_state;
};

struct	s_ari_fsm_state{
	struct s_ari_fsm_rule	rules[256];
	struct s_ari_fsm_rule	catch_rule;
};

static const struct s_ari_fsm_state	g_arithmatic_fsm_def[] = {
	[st_assert_operator] = {
		.rules = {
			['\0'] = {st_end},
			[' '] = {st_assert_operator},
			['\t'] = {st_assert_operator},
			['+'] = {st_operator},
			['-'] = {st_operator},
			['*'] = {st_operator},
			['/'] = {st_operator},
			['%'] = {st_operator},
			['<'] = {st_operator},
			['>'] = {st_operator},
			['='] = {st_operator},
			['!'] = {st_operator},
			['&'] = {st_operator},
			['|'] = {st_operator},
		},
		.catch_rule = {invalid_state},
	},
	[st_operator] = {
		.rules = {
			['\0'] = {st_end},
			[' '] = {st_encounterer},
			['\t'] = {st_encounterer},
			['0'] = {st_number},
			['1'] = {st_number},
			['2'] = {st_number},
			['3'] = {st_number},
			['4'] = {st_number},
			['5'] = {st_number},
			['6'] = {st_number},
			['7'] = {st_number},
			['8'] = {st_number},
			['9'] = {st_number},
			['+'] = {st_operator},
			['-'] = {st_operator},
			['*'] = {st_operator},
			['/'] = {st_operator},
			['%'] = {st_operator},
			['<'] = {st_operator},
			['>'] = {st_operator},
			['='] = {st_operator},
			['!'] = {st_operator},
			['&'] = {st_operator},
			['|'] = {st_operator},
		},
		.catch_rule = {st_variable},
	},
	[st_encounterer] = {
		.rules = {
			['\0'] = {st_end},
			[' '] = {st_encounterer},
			['\t'] = {st_encounterer},
			['0'] = {st_number},
			['1'] = {st_number},
			['2'] = {st_number},
			['3'] = {st_number},
			['4'] = {st_number},
			['5'] = {st_number},
			['6'] = {st_number},
			['7'] = {st_number},
			['8'] = {st_number},
			['9'] = {st_number},
			['+'] = {st_operator},
			['-'] = {st_operator},
			['*'] = {st_operator},
			['/'] = {st_operator},
			['%'] = {st_operator},
			['<'] = {st_operator},
			['>'] = {st_operator},
			['='] = {st_operator},
			['!'] = {st_operator},
			['&'] = {st_operator},
			['|'] = {st_operator},
		},
		.catch_rule = {st_variable},
	},
	[st_variable] = {
		.rules = {
			['\0'] = {st_end},
			['+'] = {st_operator},
			['-'] = {st_operator},
			['*'] = {st_operator},
			['/'] = {st_operator},
			['%'] = {st_operator},
			['<'] = {st_operator},
			['>'] = {st_operator},
			['='] = {st_operator},
			['!'] = {st_operator},
			['&'] = {st_operator},
			['|'] = {st_operator},
		},
		.catch_rule = {st_assert_operator},
	},
	[st_number] = {
		.rules = {
			['\0'] = {st_end},
			['+'] = {st_operator},
			['-'] = {st_operator},
			['*'] = {st_operator},
			['/'] = {st_operator},
			['%'] = {st_operator},
			['<'] = {st_operator},
			['>'] = {st_operator},
			['='] = {st_operator},
			['!'] = {st_operator},
			['&'] = {st_operator},
			['|'] = {st_operator},
		},
		.catch_rule = {st_assert_operator},
	},
};

#endif
