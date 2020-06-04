/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_word.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 10:58:15 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/20 10:58:15 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"
#include "quote_trans_table.h"

static size_t	process_init(t_shell *shell, char **word, t_q_table table)
{
	t_env	*env;
	size_t	read;
	size_t	write;

	read = 0;
	write = 0;
	if (word == NULL || *word == NULL)
		return (SIZE_MAX);
	if (shell == NULL)
		env = NULL;
	else
		env = shell->env;
	if (table == ALL_QUOTES_TABLE)
		expand_home(env, word, &read, &write);
	return (write);
}

static int		init_vars(size_t *read, size_t *write,
											t_q_state *state, size_t init)
{
	if (init == SIZE_MAX)
		return (-1);
	*read = init;
	*write = init;
	*state = no_quote;
	return (0);
}

int				process_word(t_shell *shell, char **word, t_q_table table)
{
	size_t		read;
	size_t		write;
	t_q_rules	rules;
	t_q_state	state;

	if (init_vars(&read, &write, &state, process_init(shell, word, table)) != 0)
		return (-1);
	while (state != q_eof)
	{
		rules = g_quote_trans[table][state].rules[(size_t)(*word)[read]];
		if (rules.next_state == q_invalid)
			rules = g_quote_trans[table][state].catch_state;
		if (rules.add_char == Q_REMOVE_BS || rules.add_char == Q_REMOVE_SKIP)
			write--;
		if (rules.add_char == Q_ADD_CHAR || rules.add_char == Q_REMOVE_BS)
		{
			(*word)[write] = (*word)[read];
			write++;
		}
		else if (rules.add_char == Q_EXPAND_VAR)
			expand_variable(shell, word, &read, &write);
		read++;
		state = rules.next_state;
	}
	return (0);
}
