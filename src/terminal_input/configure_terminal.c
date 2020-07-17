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
#include "prompt.h"
#include "signal_handler.h"
#include "environment.h"

static void		set_terminal_ownership(t_shell *shell)
{
	shell->pid = getpid();
	shell->pgid = getpgid(shell->pid);
	while (tcgetpgrp(STDIN_FILENO) != shell->pgid)
	{
		kill(-1 * shell->pgid, SIGTTIN);
		shell->pgid = getpgid(shell->pid);
	}
	setpgid(shell->pid, shell->pid);
	shell->pgid = shell->pid;
	tcsetpgrp(STDIN_FILENO, shell->pgid);
}

static void		set_terminal_attr(t_shell *shell, struct termios *orig)
{
	struct termios			shell_temp;
	char					*temp;

	if (shell == NULL)
		return ;
	temp = ft_getenv(shell->env, "TERM", ENV_VAR);
	if (temp == NULL)
		temp = "dumb";
	tgetent(NULL, temp);
	free(temp);
	shell_temp = *orig;
	shell_temp.c_lflag &= ~(ECHO | ICANON);
	shell_temp.c_cc[VMIN] = 1;
	shell_temp.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &shell_temp);
	shell->term = shell_temp;
}

void			configure_terminal(t_shell *shell, int activator)
{
	static struct termios	orig;

	if (activator == 1 || activator == 2)
	{
		tcgetattr(STDIN_FILENO, &orig);
	}
	if (activator > 1)
	{
		set_terminal_ownership(shell);
		set_terminal_attr(shell, &orig);
	}
	if (activator == 0)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &orig);
	}
}
