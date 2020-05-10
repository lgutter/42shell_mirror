/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   configure_terminal.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkroeke <dkroeke@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/06 17:03:13 by dkroeke       #+#    #+#                 */
/*   Updated: 2020/05/09 23:42:02 by devan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "input_control.h"

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
		shell_temp.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
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

void		get_winsize(t_shell *shell)
{
	t_cursor *curs;

	curs = &shell->cursor;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &shell->winsize);
	curs->max.x = (size_t)shell->winsize.ws_col;
	curs->max.y = (size_t)shell->winsize.ws_row;
}
