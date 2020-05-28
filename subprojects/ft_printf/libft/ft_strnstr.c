/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 12:30:58 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/31 12:30:59 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_word(const char *string, const char *word, size_t len)
{
	size_t index;

	index = 0;
	while (word[index] != '\0')
	{
		if (word[index] != string[index] || index >= len)
		{
			return (0);
		}
		index++;
	}
	return (1);
}

char		*ft_strnstr(const char *string, const char *word, size_t len)
{
	size_t index;

	index = 0;
	if (word[0] == '\0')
	{
		return ((char *)string);
	}
	while (string[index] != '\0' && index < len)
	{
		if (string[index] == word[0])
		{
			if (check_word(&string[index], word, len - index) == 1)
			{
				return ((char *)&string[index]);
			}
		}
		index++;
	}
	return (NULL);
}
