/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils_1.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 12:48:27 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/15 12:48:27 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "input_control.h"
#include "quote_trans_table.h"

int			check_quote(char *word)
{
	int			quote;
	size_t		i;
	t_q_rules	rules;
	t_q_state	state;

	state = no_quote;
	i = 0;
	quote = 0;
	while (1)
	{
		rules = g_quote_trans[state].rules[(size_t)word[i]];
		if (rules.next_state == invalid)
			rules = g_quote_trans[state].catch_state;
		if (state == dquote && rules.next_state == no_quote)
			quote = 2;
		if (state == squote && rules.next_state == no_quote)
			quote = 1;
		if (rules.next_state == eof && (state == squote || state == dquote))
			return (state == squote ? -1 : -2);
		else if (rules.next_state == eof)
			return (quote);
		state = rules.next_state;
		i++;
	}
}

static void	str_cpy_no_quotes(char *dst, const char *src)
{
	size_t		i;
	size_t		j;
	t_q_rules	rules;
	t_q_state	state;

	i = 0;
	j = 0;
	state = no_quote;
	while (1)
	{
		rules = g_quote_trans[state].rules[(size_t)src[i]];
		if (rules.next_state == invalid)
			rules = g_quote_trans[state].catch_state;
		if (rules.add_char == ADD_CHAR)
		{
			dst[j] = src[i];
			j++;
		}
		if (rules.next_state == eof)
			return ;
		state = rules.next_state;
		i++;
	}
}

int			remove_quotes(char **word)
{
	char	*temp;
	int		quotes;
	size_t	len;

	quotes = check_quote(*word);
	if (quotes < 0 || (quotes == 0 && ft_strchr(*word, '\\') == NULL))
		return (quotes);
	quotes = count_quote_chars(*word);
	len = ft_strlen(*word);
	len -= (quotes);
	temp = (char *)ft_memalloc(len + 1);
	str_cpy_no_quotes(temp, *word);
	if (temp == NULL)
		return (-1);
	free(*word);
	*word = temp;
	return (0);
}

int			complete_quote(t_shell *shell, char **word)
{
	char	*buff;
	char	*temp;
	int		quotes;

	temp = ft_strdup(*word);
	if (temp == NULL)
		return (-1);
	buff = NULL;
	quotes = check_quote(temp);
	while (quotes < 0)
	{
		ft_strexpand(&temp, "\n");
		buff = prompt_shell(shell, quotes == -2 ? PROMPT_DQUOTE : PROMPT_QUOTE);
		ft_strexpand(&temp, buff);
		free(buff);
		if (temp == NULL)
			return (-1);
		quotes = check_quote(temp);
	}
	free(*word);
	*word = temp;
	return (0);
}
