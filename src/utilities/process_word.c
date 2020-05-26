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

#include "executor.h"

static int	get_exp_opts(int process_opts, int quote_type)
{
	int	opts;

	opts = VAR_TYPE;
	if (quote_type != 1 && (process_opts & WORD_UNQUOTE) != 0)
		opts |= QUOTE_VAR;
	return (opts);
}

int	process_word(t_shell *shell, char **word, int opts)
{
	int	quote_type;

	if (word == NULL || *word == NULL)
		return (-1);
	quote_type = check_quote(*word);
	if ((opts & WORD_FIX_QUOTES) != 0 && quote_type < 0)
	{
		if (complete_quote(shell, word) != 0)
			return (-1);
		quote_type = check_quote(*word);
	}
	if ((opts & WORD_FORCE_EXPAND) != 0 ||
		((opts & WORD_EXPAND) != 0 && (quote_type == 0 || quote_type == 2)))
	{
		if (expand_variable(shell, word, get_exp_opts(opts, quote_type)) != 0)
			return (-1);
	}
	if ((opts & WORD_UNQUOTE) != 0 && count_quote_chars(*word) > 0)
	{
		if (remove_quotes(word) != 0)
			return (-1);
	}
	return (0);
}
