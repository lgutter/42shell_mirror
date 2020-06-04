/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_redirects.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/07 14:00:07 by lgutter       #+#    #+#                 */
/*   Updated: 2020/05/07 14:00:07 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

static int	process_here_doc(t_shell *shell, t_io_here *io_here)
{
	int	quotes;

	quotes = check_quote(io_here->here_end);
	if (quotes == 0 && ft_strchr(io_here->here_end, '\\') != NULL)
		quotes = 3;
	if (process_word(shell, &(io_here->here_end), HERE_END_TABLE))
		return (-1);
	if (get_here_doc(io_here, shell) != 0)
		return (handle_error(malloc_error));
	if (quotes == 0)
	{
		return (process_word(shell, &(io_here->here_doc), HEREDOCS_TABLE));
	}
	return (0);
}

static int	process_io_file(t_shell *shell, t_io_file *io_file)
{
	const char	*filename;
	size_t		i;

	i = 0;
	if (process_word(shell, &(io_file->filename), ALL_QUOTES_TABLE))
		return (-1);
	filename = io_file->filename;
	if (io_file->redirect_op == redirect_fd_in ||
		io_file->redirect_op == redirect_fd_out)
	{
		if (filename[0] == '-' && filename[1] == '\0')
			return (0);
		while (filename[i] != '\0')
		{
			if (ft_isdigit(filename[i]) == 0)
				return (handle_error_str(ambig_redirect, filename));
			i++;
		}
	}
	return (0);
}

int			process_redirects(t_shell *shell, t_io_redirect *redirects)
{
	while (redirects != NULL)
	{
		if (redirects->io_number != NULL)
			redirects->io_fd = ft_atoi(redirects->io_number);
		if (redirects->io_file != NULL && redirects->io_file->filename != NULL)
		{
			if (process_io_file(shell, redirects->io_file) != 0)
				return (-1);
		}
		else if (redirects->io_here != NULL)
		{
			if (process_here_doc(shell, redirects->io_here) != 0)
				return (-1);
		}
		else
		{
			return (handle_error_str(parsing_error, "empty redirect"));
		}
		redirects = redirects->next;
	}
	return (0);
}
