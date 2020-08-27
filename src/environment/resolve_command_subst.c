/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   resolve_command_subst.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nloomans <nloomans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 12:57:26 by nloomans      #+#    #+#                 */
/*   Updated: 2020/08/27 17:57:26 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "environment.h"
#include "substitution.h"
#include "handle_input.h"
#include "processing.h"

static void		exec_command_and_exit(int output_fd, const char *command,
					size_t str_len, t_shell *shell)
{
	char	*input;

	input = ft_strndup(command, str_len);
	if (input == NULL)
	{
		handle_error(malloc_error);
		exit(1);
	}
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
		handle_error(dup2_fd_fail);
		exit(1);
	}
	if (shell != NULL)
		shell->interactive = false;
	handle_input(shell, &input);
	exit(0);
}

static char		*read_to_string(int fd)
{
	char	*ret;
	int		read_amount;
	char	read_buffer[2048];

	ret = ft_strnew(0);
	if (ret == NULL)
		return (NULL);
	while (true)
	{
		read_amount = read(fd, read_buffer, sizeof(read_buffer) - 1);
		if (read_amount < 0)
		{
			ft_strdel(&ret);
			return (NULL);
		}
		if (read_amount == 0)
			break ;
		read_buffer[read_amount] = '\0';
		ft_strexpand(&ret, read_buffer);
		if (ret == NULL)
			return (NULL);
	}
	while (ret[0] != '\0' && ret[ft_strlen(ret) - 1] == '\n')
		ret[ft_strlen(ret) - 1] = '\0';
	return (ret);
}

static int		resolve_command_subst(char **out, t_shell *shell,
					const char *subst)
{
	size_t	subst_len;
	int		fork_pipe[2];
	pid_t	pid;

	subst_len = subst_length(subst + 1);
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
		exec_command_and_exit(fork_pipe[1], subst + 2, subst_len - 2, shell);
	close(fork_pipe[1]);
	*out = read_to_string(fork_pipe[0]);
	close(fork_pipe[0]);
	if (*out == NULL)
		return (-malloc_error);
	return (subst_len + 1);
}

int				expand_command_subst(t_shell *shell,
									char **string, size_t *read, size_t *write)
{
	int		len;
	char	*expanded;
	char	*new;

	if (string == NULL || *string == NULL || read == NULL || write == NULL)
		return (-1);
	len = resolve_command_subst(&expanded, shell, *string + *read);
	if (len < 0)
		return (-len);
	ft_asprintf(&new, "%.*s%s%s",
		*write, *string, expanded, *string + *read + len);
	if (new == NULL)
	{
		ft_strdel(&expanded);
		return (malloc_error);
	}
	ft_strdel(string);
	*string = new;
	*write += ft_strlen(expanded);
	*read = *write - 1;
	ft_strdel(&expanded);
	return (no_error);
}
