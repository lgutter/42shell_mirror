/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.h                                          :+:    :+:            */
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
					const char *subst, size_t subst_len)
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
		close(fork_pipe[0]);
		subst_exec_command_and_exit((int[]){fork_pipe[1], STDOUT_FILENO},
			subst + 2, subst_len - 2, shell);
	}
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
	size_t	subst_len;

	if (string == NULL || *string == NULL || read == NULL || write == NULL)
		return (-1);
	subst_len = subst_length(*string + *read + 1);
	len = resolve_command_subst(&expanded, shell, *string + *read, subst_len);
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
