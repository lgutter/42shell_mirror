/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils_2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 12:48:27 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/15 12:48:27 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "quote_trans_table.h"

int			count_quote_chars(char *str)
{
	int			count;
	size_t		i;
	t_q_rules	rules;
	t_q_state	state;

	state = no_quote;
	i = 0;
	count = 0;
	while (1)
	{
		rules = g_quote_trans[state].rules[(size_t)str[i]];
		if (rules.next_state == invalid)
			rules = g_quote_trans[state].catch_state;
		if (rules.add_char == SKIP_CHAR)
			count++;
		if (rules.next_state == eof)
			return (count);
		state = rules.next_state;
		i++;
	}
}

char		*backslash_quotes(char *str)
{
	size_t	s_i;
	size_t	t_i;
	size_t	count;
	char	*temp;

	s_i = 0;
	t_i = 0;
	count = count_quote_chars(str);
	temp = ft_memalloc(ft_strlen(str) + count + 1);
	if (temp == NULL)
		return (NULL);
	while (str[s_i] != '\0')
	{
		if (str[s_i] == '"' || str[s_i] == '\'' || str[s_i] == '\\')
		{
			temp[t_i] = '\\';
			t_i++;
		}
		temp[t_i] = str[s_i];
		s_i++;
		t_i++;
	}
	return (temp);
}
