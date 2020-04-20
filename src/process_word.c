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

#include "handle_input.h"

int	process_word(t_shell *shell, t_env *env_list, char **word, char expand)
{
	int	quote_type;

	quote_type = check_quote(*word);
	if (quote_type < 0)
	{
		if (complete_quote(shell, word) != 0)
			return (-1);
		quote_type = check_quote(*word);
	}
	if (expand == 'y' && (quote_type == 0 || quote_type == 2))
	{
		if (expand_variable(env_list, word) != 0)
			return (-1);
	}
	if (count_quote_chars(*word) > 0)
	{
		if (remove_quotes(word) != 0)
			return (-1);
	}
	return (0);
}
