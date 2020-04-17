/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 10:43:04 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/15 10:43:04 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_strexpand(char **source, const char *addition)
{
	void *temp;

	temp = *source;
	if (*source == NULL)
	{
		*source = ft_strdup(addition);
	}
	else if (addition != NULL)
	{
		*source = ft_strjoin(*source, addition);
		free(temp);
	}
}

void	str_expand_triple(char **source, char *add1, char *add2)
{
	ft_strexpand(source, add1);
	if (*source == NULL)
		return ;
	ft_strexpand(source, add2);
}

char	*ft_strndup(const char *string, size_t len)
{
	char	*ret;
	size_t	index;

	index = 0;
	if (string == NULL)
	{
		return (NULL);
	}
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret != NULL)
	{
		while (index < len)
		{
			ret[index] = string[index];
			index++;
		}
		ret[index] = '\0';
	}
	return (ret);
}

size_t	ft_strlenc(const char *string, int delim, size_t size)
{
	size_t len;

	len = 0;
	while (string[len] != (char)delim && len < size)
		len++;
	return (len);
}

char	*ft_strcdup(const char *string, char delim)
{
	size_t	len;

	if (string == NULL)
	{
		return (NULL);
	}
	len = ft_strlenc(string, delim, ft_strlen(string));
	return (ft_strndup(string, len));
}
