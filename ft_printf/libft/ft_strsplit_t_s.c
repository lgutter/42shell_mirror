/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit_t_s.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 18:29:22 by lgutter       #+#    #+#                 */
/*   Updated: 2020/02/10 16:51:47 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_tab_space(int c)
{
	if (c == ' ' || c == '\t')
	{
		return (1);
	}
	return (0);
}

static size_t	ft_wordcount_t_s(char const *string)
{
	size_t	index;
	size_t	wordcount;

	index = 0;
	wordcount = 0;
	while (string[index] != '\0')
	{
		while (ft_is_tab_space(string[index]) == 1)
		{
			index++;
		}
		if (string[index] != '\0')
		{
			wordcount++;
		}
		while (ft_is_tab_space(string[index]) == 0 && string[index] != '\0')
		{
			index++;
		}
	}
	return (wordcount);
}

static char		*ft_writeword_t_s(char const *string, size_t index)
{
	size_t	len;
	char	*ret;

	len = index;
	while (ft_is_tab_space(string[len]) == 0 && string[len] != '\0')
		len++;
	ret = (char *)ft_memalloc(sizeof(char) * len + 1);
	if (ret == NULL)
		return (NULL);
	len = 0;
	while (ft_is_tab_space(string[index]) == 0 && string[index] != '\0')
	{
		ret[len] = string[index];
		index++;
		len++;
	}
	ret[len] = '\0';
	return (ret);
}

char			**ft_strsplit_t_s(char const *string)
{
	char	**ret;
	size_t	index;
	size_t	wordcount;
	size_t	wordindex;

	index = 0;
	wordcount = ft_wordcount_t_s(string);
	wordindex = 0;
	ret = (char **)ft_memalloc(sizeof(char *) * (wordcount + 1));
	if (ret == NULL)
		return (NULL);
	ret[wordcount] = NULL;
	while (string[index] != '\0' && wordindex < wordcount)
	{
		while (ft_is_tab_space(string[index]) == 1)
			index++;
		if (string[index] != '\0')
			ret[wordindex] = ft_writeword_t_s(string, index);
		wordindex++;
		while (ft_is_tab_space(string[index]) == 0 && string[index] != '\0')
			index++;
	}
	return (ret);
}
