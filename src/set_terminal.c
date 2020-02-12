/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_terminal.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 12:24:22 by dkroeke        #+#    #+#                */
/*   Updated: 2020/02/12 12:24:22 by dkroeke       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void		configure_terminal(t_shell *shell, int activator)
{
	static struct termios orig;

	if (activator == 1)
	{
		tcgetattr(STDIN_FILENO, &orig);
		shell->term = orig;
		shell->term.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
		shell->term.c_iflag &= ~(IXON);
		shell->term.c_cc[VMIN] = 0;
		shell->term.c_cc[VTIME] = 1;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->term);
	}
	if (activator == 0)
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig);
}
