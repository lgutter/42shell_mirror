/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cetushell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: Invalid date        by                #+#    #+#                */
/*   Updated: 0003/01/01 00:00:00 by               ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CETUSHELL_H
# define CETUSHELL_H
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <term.h>
# include "ft_printf.h"
# include "libft.h"

# define INPUT_BUFF_SIZE 20
# define CUR_BUFF_SIZE 32
# define REALLOC_SIZE 8

typedef struct		s_buff
{
	char			*buff;
	char			*copy;
	size_t			copy_size;
	size_t			buff_size;
	size_t			len;
	size_t			index;
	size_t			rv_start;
	size_t			rv_end;
}					t_buff;

typedef struct		s_point
{
	size_t				x;
	size_t				y;
}					t_point;

typedef struct		s_cursor
{
	t_point			start;
	t_point			current;
	t_point			max;
	char			cur_buff[CUR_BUFF_SIZE];
}					t_cursor;

typedef struct		s_shell
{
	struct termios	term;
	char			**envi;
	t_cursor		cursor;
	struct winsize	winsize;
	t_buff			*buffer;
}					t_shell;

#endif
