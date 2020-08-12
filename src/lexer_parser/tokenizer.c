/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:52:43 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/14 11:52:43 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "utils.h"
#include "vecstr.h"

static t_rules	init_state(t_state cur_state, char next)
{
	t_rules	state_rules;

	state_rules = g_token_trans[cur_state].rules[(size_t)next];
	if (state_rules.next_state == invalid)
	{
		state_rules = g_token_trans[cur_state].catch_state;
	}
	return (state_rules);
}

static int		handle_token(t_rules state_rules, t_token **start,
							t_vecstr *buff, char input)
{
	int	ret;

	ret = 0;
	if (ret == 0 && state_rules.add_char == ADD_CHAR_PRE)
		ret = vecstr_add(buff, &input, 1);
	if (ret == 0 && state_rules.delimit_type != undetermined)
		ret = add_token(start, state_rules.delimit_type, buff);
	if (ret == 0 && state_rules.add_char == ADD_CHAR_POST)
		ret = vecstr_add(buff, &input, 1);
	if (ret != no_error)
		handle_error(ret);
	return (ret);
}

static int		check_unquoted(t_shell *shell, t_rules *rules,
								char **input, size_t *i)
{
	if (rules->next_state == pre_unt_pipe && *i > 0)
		(*i)--;
	if (rules->next_state == unt_dquote ||
		rules->next_state == unt_squote ||
		rules->next_state == unt_backslash ||
		rules->next_state == unt_pipe)
	{
		if (complete_unterminated(shell, input) != 0)
			return (-1);
	}
	else
		return (0);
	*rules = init_state(rules->next_state, (*input)[*i]);
	return (0);
}

t_token			*tokenizer(t_shell *shell, char **input)
{
	t_rules			state_rules;
	t_token			*start;
	t_state			cur_state;
	static t_vecstr	buff;
	size_t		i;

	if (input == NULL || *input == NULL)
		return (NULL);
	start = NULL;
	cur_state = blank;
	i = 0;
	while (1)
	{
		state_rules = init_state(cur_state, (*input)[i]);
		if (check_unquoted(shell, &state_rules, input, &i) != 0)
			return (free_token_list_empty_buff(&start, &buff));
		if (handle_token(state_rules, &start, &buff, (*input)[i]) != 0)
			return (free_token_list_empty_buff(&start, &buff));
		if (state_rules.next_state == eof)
			return (start);
		cur_state = state_rules.next_state;
		i++;
	}
}
