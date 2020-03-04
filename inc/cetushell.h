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

# define PROMPT_LEN 10

typedef struct		s_buff
{
	char			buff[2048];
	size_t			len;
	size_t			index;
}					t_buff;

typedef struct		s_cursor
{
	ssize_t			x;
	size_t			y;
	char			cur_buff[32];
	size_t			layer;
	size_t			x_max;
	size_t			y_max;
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
void		get_cursor_pos(t_cursor *cursor, int init);
int			prompt_shell(t_shell *shell);
int			read_input(t_shell *shell);
void		init_buffs(t_shell *shell);
void		remove_char(t_buff *buffer);
void		refresh_prompt(t_buff buffer, t_cursor cursor);

#endif
