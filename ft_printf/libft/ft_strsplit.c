/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 18:29:22 by lgutter       #+#    #+#                 */
/*   Updated: 2019/01/21 18:29:32 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordcount(char const *string, char delim)
{
	size_t	index;
	size_t	wordcount;

	index = 0;
	wordcount = 0;
	while (string[index] != '\0')
	{
		while (string[index] == delim)
		{
			index++;
		}
		if (string[index] != '\0')
		{
			wordcount++;
		}
		while (string[index] != delim && string[index] != '\0')
		{
			index++;
		}
	}
	return (wordcount);
}

static char		*ft_writeword(char const *string, size_t index, char delim)
{
	size_t	len;
	char	*ret;

	len = index;
	while (string[len] != delim && string[len] != '\0')
		len++;
	ret = (char *)malloc(sizeof(char) * ((len - index) + 1));
	if (!ret)
		return (NULL);
	ret[len - index] = '\0';
	len = 0;
	while (string[index] != delim && string[index] != '\0')
	{
		ret[len] = string[index];
		index++;
		len++;
	}
	ret[len] = '\0';
	return (ret);
}

char			**ft_strsplit(char const *string, char delim)
{
	char	**ret;
	size_t	index;
	size_t	wordcount;
	size_t	wordindex;

	index = 0;
	wordcount = ft_wordcount(string, delim);
	wordindex = 0;
	ret = (char **)malloc(sizeof(char *) * (wordcount + 1));
	if (!ret)
		return (NULL);
	ret[wordcount] = NULL;
	while (string[index] != '\0' && wordindex < wordcount)
	{
		while (string[index] == delim)
			index++;
		if (string[index] != '\0')
			ret[wordindex] = ft_writeword(string, index, delim);
		wordindex++;
		while (string[index] != delim && string[index] != '\0')
			index++;
	}
	return (ret);
}
