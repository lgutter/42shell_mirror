/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 11:51:53 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/31 11:51:54 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_word(const char *string, const char *word)
{
	size_t index;

	index = 0;
	while (word[index] != '\0')
	{
		if (word[index] != string[index])
		{
			return (0);
		}
		index++;
	}
	return (1);
}

char		*ft_strstr(const char *string, const char *word)
{
	size_t index;

	index = 0;
	if (string == NULL || word == NULL || word[0] == '\0')
	{
		return ((char *)string);
	}
	while (string[index] != '\0')
	{
		if (string[index] == word[0])
		{
			if (check_word(&string[index], word) == 1)
			{
				return ((char *)&string[index]);
			}
		}
		index++;
	}
	return (NULL);
}
