/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nloomans <nloomans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 0000/00/00 00:00:00 by nloomans      #+#    #+#                 */
/*   Updated: 9999/99/99 99:99:99 by nloomans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "environment.h"
#include "substitution.h"
#include "handle_input.h"
#include "processing.h"

int				launch_process(const char *command, size_t command_len,
					t_shell *shell, bool is_left)
{
	int		fork_pipe[2];
	pid_t	pid;

	if (pipe(fork_pipe) == -1)
		return (-pipe_failure);
	pid = fork();
	if (pid == -1)
	{
		close(fork_pipe[0]);
		close(fork_pipe[1]);
		return (-fork_failure);
	}
	if (pid == 0)
	{
		close(fork_pipe[is_left ? 0 : 1]);
		if (is_left)
			subst_exec_command_and_exit((int[]){fork_pipe[1], STDOUT_FILENO},
				command, command_len, shell);
		else
			subst_exec_command_and_exit((int[]){fork_pipe[0], STDIN_FILENO},
				command, command_len, shell);
	}
	close(fork_pipe[is_left ? 1 : 0]);
	return (fork_pipe[is_left ? 0 : 1]);
}

static int		push_process_fd(t_fd_list **fd_list, int fd)
{
	t_fd_list	to_insert;

	to_insert = (t_fd_list){ fd, .og_fd = -1, .next = *fd_list };
	*fd_list = ft_memdup(&to_insert, sizeof(to_insert));
	if (*fd_list == NULL)
	{
		*fd_list = to_insert.next;
		return (-1);
	}
	return (0);
}

int				expand_process_subst(t_shell *shell,
					char **string, size_t *read, size_t *write)
{
	size_t		subst_len;
	char		*new;
	const bool	is_left = (*string)[*read] == '<';
	int			fd;

	if (string == NULL || *string == NULL || read == NULL || write == NULL)
		return (-1);
	subst_len = subst_length(*string + *read + 1);
	fd = launch_process(*string + *read + 2, subst_len - 2, shell, is_left);
	if (fd < 0)
		return (-fd);
	ft_asprintf(&new, "%.*s/dev/fd/%d%s",
				*write, *string, fd, *string + *read + subst_len + 1);
	if (new == NULL)
		return (malloc_error);
	ft_strdel(string);
	*string = new;
	*write += ft_strlen("/dev/fd/") + ft_nbrlenbase(fd, 10);
	*read = *write - 1;
	if (push_process_fd(&shell->process_subst_fds, fd) == -1)
		return (malloc_error);
	return (no_error);
}

t_fd_list		*close_process_fds(t_fd_list *node)
{
	if (node != NULL)
	{
		node->next = close_process_fds(node->next);
		close(node->fd);
		free(node);
	}
	return (NULL);
}
