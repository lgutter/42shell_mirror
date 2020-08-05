/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_read_buff.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 15:22:06 by lgutter       #+#    #+#                 */
/*   Updated: 2020/08/05 15:22:06 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cetushell.h"

void	free_read_buff(t_buff *buffer)
{
	if (buffer == NULL)
		return ;
	free(buffer->read_buff);
	buffer->read_buff = NULL;
	buffer->read_index = 0;
}

void	update_read_buff(t_shell *shell)
{
	struct termios	shell_temp;
	char			temp[INP_BUFF_SIZE];

	if (shell == NULL || shell->buffer == NULL)
		return ;
	shell_temp = shell->term;
	shell_temp.c_cc[VMIN] = 0;
	ft_memset(temp, '\0', INP_BUFF_SIZE);
	if (shell->interactive)
		tcsetattr(STDERR_FILENO, TCSADRAIN, &shell_temp);
	while (read(STDIN_FILENO, temp, INP_BUFF_SIZE) > 0)
	{
		ft_strexpand(&(shell->buffer->read_buff), temp);
		ft_memset(temp, '\0', INP_BUFF_SIZE);
	}
	if (shell->interactive)
		tcsetattr(STDERR_FILENO, TCSADRAIN, &(shell->term));
}
