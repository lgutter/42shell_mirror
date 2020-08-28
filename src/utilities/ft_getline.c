/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_getline.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 18:13:44 by lgutter       #+#    #+#                 */
/*   Updated: 2020/08/28 18:13:44 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int		get_line_read_loop(const int fd, t_vecstr *vector)
{
	char	buff;
	int		ret;

	while (true)
	{
		ret = read(fd, &buff, 1);
		if (ret <= 0 || buff == '\n')
			break ;
		if (vecstr_add(vector, &buff, 1) != 0)
		{
			ret = -1;
			break ;
		}
	}
	return (ret);
}

int				ft_getline(const int fd, char **line)
{
	t_vecstr	vector;
	int			ret;

	if (line == NULL)
		return (-1);
	*line = NULL;
	vector = new_vecstr(NULL);
	ret = get_line_read_loop(fd, &vector);
	if (ret >= 0)
	{
		if (vector.len == 0)
			*line = ft_strdup("");
		else
		{
			ret = 1;
			*line = ft_strdup(vector.string);
		}
		if (*line == NULL)
			ret = -1;
	}
	clear_vecstr(&vector);
	return (ret);
}
