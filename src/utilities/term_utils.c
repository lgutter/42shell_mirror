/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 15:49:31 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/02 15:49:31 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"
#include "prompt.h"
#include "signal_handler.h"
#include "environment.h"

static int	ft_puterrchar(int c)
{
	return (write(STDERR_FILENO, &c, 1));
}

void		send_terminal(char *command)
{
	tputs(tgetstr(command, NULL), 1, ft_puterrchar);
}

void		get_winsize(t_cursor *cursor, size_t len)
{
	struct winsize winsize;

	if (cursor == NULL)
		return ;
	get_cursor_pos(cursor, len);
	if (ioctl(STDERR_FILENO, TIOCGWINSZ, &winsize) == 0)
	{
		cursor->max.x = (size_t)winsize.ws_col;
		cursor->max.y = (size_t)winsize.ws_row;
	}
	g_signal_handler = 0;
}
