/* ************************************************************************** */
/*                                                                            */
/*   cetushell - 21 Shell                                 ::::::::            */
/*                                                      :+:    :+:            */
/*   By: dkroeke <dkroeke@student.codam.nl>            +:+                    */
/*       lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*                                                 #+#    #+#                 */
/*   License: GPLv3                                ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"

static int	ft_putchar(int c)
{
	return (write(STDERR_FILENO, &c, 1));
}

/**
 * this function will is able to send (termcap)codes specified by terminfo(5).
 */
void		send_terminal(char *command)
{
	tputs(tgetstr(command, NULL), 1, ft_putchar);
}

/**
 * configure the terminal to run in RAW mode. RAW mode will not echo input
 * directly to the terminal but lets you process the input into your own
 * interpretation. 
 * The settings for the terminal before cetushell will be stored into a static
 * and with terminating the program these settings will be returned. 
 * tgetent will get the current terminal information.
 */
void		configure_terminal(t_shell *shell, int activator)
{
	static struct termios orig;

	if (activator == 1)
	{
		tgetent(NULL, getenv("TERM"));
		tcgetattr(STDIN_FILENO, &orig);
		shell->term = orig;
		shell->term.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
		shell->term.c_iflag &= ~(IXON);
		shell->term.c_cc[VMIN] = 0;
		shell->term.c_cc[VTIME] = 1;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->term);
	}
	if (activator == 0)
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig);
}

/** will get the current window size of the terminal and will put it into
 * a winsize struct. This is needed for printing newlines correctly at 
 * end of the screen.
 */
void		get_winsize(t_shell *shell)
{
	t_cursor *curs;

	curs = &shell->cursor;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &shell->winsize);
	curs->max.x = shell->winsize.ws_col;
	curs->max.y = shell->winsize.ws_row;
}
