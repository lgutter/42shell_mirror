/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/14 14:37:43 by lgutter       #+#    #+#                 */
/*   Updated: 2019/02/14 14:37:44 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define BUFF_SIZE	32

typedef struct		s_cache
{
	int				fd;
	char			*content;
	size_t			size;
	struct s_cache	*next;
}					t_cache;

int					get_next_line(const int fd, char **line);

#endif
