/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils_1.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 12:48:27 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/23 16:31:14 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "prompt.h"
#include "quote_trans_table.h"
#include "signal_handler.h"

int			check_quote(char *word)
{
	int			quote;
	t_q_rules	rules;
	t_q_state	state;

	if (word == NULL)
		return (-1);
	state = no_quote;
	quote = 0;
	while (1)
	{
		rules = g_quote_trans[ALL_QUOTES_TABLE][state].rules[(size_t)*word];
		if (rules.next_state == q_invalid)
			rules = g_quote_trans[ALL_QUOTES_TABLE][state].catch_state;
		if (state == q_dquote && rules.next_state == no_quote)
			quote = 2;
		if (state == q_squote && rules.next_state == no_quote)
			quote = 1;
		if (rules.next_state == q_eof &&
			(state == q_squote || state == q_dquote || state == q_dq_backslash))
			return (state == q_squote ? -1 : -2);
		else if (rules.next_state == q_eof)
			return (quote);
		state = rules.next_state;
		word++;
	}
}

static void	str_cpy_no_quotes(char *dst, const char *src, int table_type)
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
		rules = g_quote_trans[table_type][state].rules[(size_t)src[i]];
		if (rules.next_state == q_invalid)
			rules = g_quote_trans[table_type][state].catch_state;
		if (rules.add_char == Q_REMOVE_BS || rules.add_char == Q_REMOVE_SKIP)
			j--;
		if (rules.add_char == Q_ADD_CHAR || rules.add_char == Q_REMOVE_BS)
		{
			dst[j] = src[i];
			j++;
		}
		if (rules.next_state == q_eof)
			return ;
		state = rules.next_state;
		i++;
	}
}

int			remove_quotes(char **word, int table_type)
{
	char	*temp;
	int		quotes;
	size_t	len;

	if (word == NULL || *word == NULL)
		return (-1);
	quotes = check_quote(*word);
	if (quotes < 0)
		return (-1);
	else if (quotes == 0 && ft_strchr(*word, '\\') == NULL)
		return (0);
	quotes = count_quote_chars(*word, table_type);
	len = ft_strlen(*word);
	len -= (quotes);
	temp = (char *)ft_memalloc(sizeof(char) * (len + 1));
	if (temp == NULL)
		return (-1);
	str_cpy_no_quotes(temp, *word, table_type);
	free(*word);
	*word = temp;
	return (0);
}

static int	get_quote_input(t_shell *shell, char **word, char **temp)
{
	char	*buff;
	int		quotes;

	buff = NULL;
	quotes = check_quote(*temp);
	while (quotes < 0)
	{
		ft_strexpand(temp, "\n");
		buff = prompt_shell(shell, quotes == -2 ? PROMPT_DQUOTE : PROMPT_QUOTE);
		ft_strexpand(temp, buff);
		free(buff);
		if (*temp == NULL)
			return (-1);
		if (g_signal_handler == SIGINT_BUFF)
		{
			*temp[0] = '\0';
			return (-1);
		}
		quotes = check_quote(*temp);
	}
	return (0);
}

int			complete_quote(t_shell *shell, char **word)
{
	char	*temp;
	int		ret;

	ret = 0;
	if (shell == NULL || word == NULL || *word == NULL)
		return (malloc_error);
	temp = ft_strdup(*word);
	if (temp == NULL)
		return (malloc_error);
	ret = get_quote_input(shell, word, &temp);
	free(*word);
	*word = temp;
	return (ret);
}
