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
# include "ft_printf.h"
# include "libft.h"
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct		s_shell
{
	struct termios	term;
	char			**envi;
}					t_shell;

void		configure_terminal(t_shell *shell, int activator);

#endif
