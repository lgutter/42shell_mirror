/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/14 14:37:52 by lgutter       #+#    #+#                 */
/*   Updated: 2020/02/04 18:17:35 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	cache_pull(int fd, t_cache **start, char **line, size_t *size)
{
	t_cache *current;
	t_cache	*previous;

	if (*start == NULL || (*start)->content == NULL || read(fd, line, 0) == -1)
		return (-1);
	current = *start;
	previous = current;
	while (current->next != NULL && current->fd != fd)
	{
		previous = current;
		current = current->next;
	}
	if (current->fd != fd && current->next == NULL)
		return (-1);
	*line = ft_memdup(current->content, current->size);
	*size = current->size;
	if (previous != current)
		previous->next = current->next;
	free(current->content);
	if (current == *start && current->next == NULL)
		*start = NULL;
	else if (current == *start && current->next != NULL)
		*start = current->next;
	free(current);
	return (1);
}

static int		list_add_new(int fd, t_cache **start, char *buf,
							ssize_t i)
{
	t_cache *new;

	if (buf == NULL || (ssize_t)ft_strlenc(buf, '\n', i - 1) >= (i - 1))
		return (0);
	new = (t_cache *)malloc(sizeof(t_cache) * 1);
	if (new == NULL)
		return (-1);
	new->fd = fd;
	if (ft_memchr(buf, '\n', i) != NULL)
	{
		new->size = i - 1 - ft_strlenc(buf, '\n', i);
		new->content = ft_memdup(&buf[ft_strlenc(buf, '\n', i) + 1], new->size);
	}
	else
	{
		new->size = i - 1;
		new->content = ft_memdup(buf, new->size);
	}
	new->next = *start;
	*start = new;
	return (1);
}

static int		finalize(int fd, t_cache **start, char **line, size_t size)
{
	if (size == 0)
	{
		ft_memexpand((void **)line, &size, "\0", 1);
		return (0);
	}
	if (list_add_new(fd, start, *line, size) == -1)
	{
		return (-1);
	}
	if (ft_memchr(*line, '\n', size) != NULL)
		size = ft_strlenc(*line, '\n', size);
	ft_memexpand((void **)line, &size, "\0", 1);
	return (size);
}

int				get_next_line(const int fd, char **line)
{
	static t_cache	*start = NULL;
	ssize_t			ret;
	char			*buffer;
	size_t			size;

	buffer = (char *)malloc(sizeof(char) * BUFF_SIZE);
	if (buffer == NULL || line == NULL || read(fd, buffer, 0) == -1)
		return (-1);
	*line = NULL;
	size = 0;
	ret = cache_pull(fd, &start, line, &size);
	if (line == NULL)
		return (-1);
	while (ft_memchr(*line, '\n', size) == NULL && ret != 0)
	{
		ret = read(fd, buffer, BUFF_SIZE);
		ft_memexpand((void **)line, &size, buffer, (size_t)ret);
	}
	ft_memdel((void **)&buffer);
	return (finalize(fd, &start, line, size));
}
