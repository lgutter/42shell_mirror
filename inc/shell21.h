/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell21.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 11:38:05 by dkroeke        #+#    #+#                */
/*   Updated: 2020/02/12 11:38:05 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <term.h>
# include "ft_printf.h"
# include "libft.h"
# include "terminal.h"

typedef struct		s_buff
{
	char			buff[2048];
	size_t			len;
}					t_buff;

typedef struct		s_cursor
{
	int				x;
	int				y;
}					t_cursor;

typedef struct		s_shell
{
	struct termios	term;
	char			**envi;
	t_cursor		cursor;
	struct winsize	winsize;
	t_buff			buffer;
}					t_shell;

void		get_winsize(t_shell *shell);
void		configure_terminal(t_shell *shell, int activator);

#endif
