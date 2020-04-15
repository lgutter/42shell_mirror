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

size_t		count_quote_chars(char *str)
{
	size_t	i;
	size_t	count;
	char	quote;

	i = 0;
	count = 0;
	quote = '\0';
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\\' && quote != '\'' && (i == 0 || str[i - 1] != '\\'))
			count++;
		else if ((str[i] == '"' || str[i] == '\'') &&
				(i == 0 || str[i - 1] != '\\'))
		{
			if (quote == '\0')
				quote = str[i];
			else if (quote == str[i])
				quote = '\0';
			count++;
		}
		i++;
	}
	return (count);
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
