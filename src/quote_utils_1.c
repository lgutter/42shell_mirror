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

int			check_quote(char *word)
{
	char	current_quote;
	int		i;

	i = 0;
	current_quote = '\0';
	while (word != NULL && word[i] != '\0')
	{
		if (word[i] == '\\')
			i += 2;
		else if (word[i] == '"' || word[i] == '\'')
		{
			current_quote = word[i];
			i++;
			while (word[i] != '\0' && (word[i] != current_quote ||
				(word[i - 1] == '\\' && current_quote != '\'')))
				i++;
			if (word[i] == '\0')
				return (current_quote == '"' ? -2 : -1);
		}
		i++;
	}
	if (current_quote != 0)
		current_quote = current_quote == '"' ? 2 : 1;
	return (current_quote);
}

static void	str_cpy_no_quotes(char *dst, const char *src)
{
	size_t	i;
	size_t	j;
	char	state;

	i = 0;
	j = 0;
	state = '\0';
	while (src[i] != '\0')
	{
		if (src[i] == '\\' && state != '\'')
			i++;
		else if (src[i] == '"' || src[i] == '\'')
		{
			if (state == '\0' && src[i] != src[i + 1])
				state = src[i];
			else if (state == src[i])
				state = '\0';
			if ((state != '\'' && src[i + 1] == '\\') || src[i] == src[i + 1])
				i++;
			i++;
		}
		dst[j] = src[i];
		i++;
		j++;
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

int			complete_quote(char **word)
{
	// char	*buff;
	char	*temp;
	int		quotes;

	temp = ft_strdup(*word);
	// buff = NULL;
	quotes = check_quote(temp);
	while (quotes < 0)
	{
		// buff = get_input(quotes == -2 ? DQUOTE : QUOTE);
		// ft_strexpand(&temp, buff);
		// free(buff);
		// if (temp == NULL)
		// 	return (-1);
		quotes = check_quote(temp);
	}
	free(*word);
	*word = temp;
	return (0);
}

