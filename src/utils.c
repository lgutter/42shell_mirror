/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/04/06 17:03:13 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"

void	ft_swap_rv(t_buff *buffer)
{
	size_t		temp;

	if (buffer->rv_start < buffer->rv_end)
	{
		temp = buffer->rv_start;
		buffer->rv_start = buffer->rv_end;
		buffer->rv_end = temp;
		buffer->rv_start++;
	}
}

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
