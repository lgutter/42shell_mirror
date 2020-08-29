/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   base.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nloomans <nloomans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 0000/00/00 00:00:00 by nloomans      #+#    #+#                 */
/*   Updated: 9999/99/99 99:99:99 by nloomans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "handle_input.h"

void		subst_exec_command_and_exit(int fd_to_fd[2], const char *command,
					size_t str_len, t_shell *shell)
{
	char	*input;

	input = ft_strndup(command, str_len);
	if (input == NULL)
	{
		handle_error(malloc_error);
		exit(1);
	}
	if (dup2(fd_to_fd[0], fd_to_fd[1]) == -1)
	{
		handle_error(dup2_fd_fail);
		exit(1);
	}
	if (shell != NULL)
		shell->interactive = false;
	handle_input(shell, &input);
	exit(0);
}
