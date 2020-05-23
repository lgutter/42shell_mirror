/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   configure_terminal.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/05/23 14:16:02 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"
#include "signal_handler.h"

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
	static struct termios	orig;
	struct termios			shell_temp;
	char					*temp;

	if (activator > 0)
	{
		temp = getenv("TERM");
		if (temp == NULL)
			temp = "xterm-256color";
		tgetent(NULL, temp);
		if (activator == 1)
			tcgetattr(STDIN_FILENO, &orig);
		shell_temp = orig;
		shell_temp.c_lflag &= ~(ECHO | ICANON | IEXTEN);
		shell_temp.c_iflag &= ~(IXON);
		shell_temp.c_cc[VMIN] = 0;
		shell_temp.c_cc[VTIME] = 1;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell_temp);
		if (shell != NULL)
			shell->term = shell_temp;
	}
	if (activator == 0)
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig);
}

void		get_winsize(t_cursor *cursor, size_t len)
{
		struct winsize winsize;

		get_cursor_pos(cursor, len);
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsize);
		cursor->max.x = (size_t)winsize.ws_col;
		cursor->max.y = (size_t)winsize.ws_row;
		g_signal_handler &= ~SIG_WINDOW;
}
