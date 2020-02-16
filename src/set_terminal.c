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

#include "terminal.h"

static int	ft_putchar(int c)
{
	return (write(STDERR_FILENO, &c, 1));
}

void		send_terminal(char *command)
{
	tputs(tgetstr(command, NULL), 1, ft_putchar);
}

void		configure_terminal(t_shell *shell, int activator)
{
	static struct termios orig;

	if (activator == 1)
	{
		tgetent(NULL, getenv("TERM"));
		tcgetattr(STDIN_FILENO, &orig);
		shell->term = orig;
		shell->term.c_lflag &= ~(ECHO | ICANON);
		//shell->term.c_iflag &= ~(IXON);
		shell->term.c_cc[VMIN] = 0;
		shell->term.c_cc[VTIME] = 1;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->term);
	}
	if (activator == 0)
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig);
}

void		get_winsize(t_shell *shell)
{
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &shell->winsize);
}
