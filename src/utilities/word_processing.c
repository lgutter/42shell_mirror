/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_processing.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 11:53:39 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/15 11:53:39 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "handle_input.h"

static int	process_redirects(t_shell *shell, t_env *env_list,
								t_simple_cmd *simple_command)
{
	t_io_redirect	*redir;

	redir = simple_command->redirects;
	while (redir != NULL)
	{
		if (redir->io_file != NULL && redir->io_file->filename != NULL)
		{
			if (process_word(shell, env_list, &(redir->io_file->filename), 'y'))
				return (-1);
		}
		if (redir->io_here != NULL && redir->io_here->here_end != NULL)
		{
			if (process_word(shell, env_list, &(redir->io_here->here_end), 'n'))
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}

static int	process_simple_cmd(t_shell *shell, t_env *env_list,
								t_simple_cmd *simple_command)
{
	t_argument		*cur_arg;

	if (process_redirects(shell, env_list, simple_command) != 0)
		return (-1);
	cur_arg = simple_command->arguments;
	while (cur_arg != NULL)
	{
		if (cur_arg->argument != NULL)
		{
			if (process_word(shell, env_list, &(cur_arg->argument), 'y') != 0)
				return (-1);
		}
		cur_arg = cur_arg->next;
	}
	return (0);
}

int			word_processing(t_shell *shell, t_env *env_list,
							t_complete_cmd *complete_command)
{
	t_complete_cmd	*command;
	t_pipe_sequence	*pipe_seq;

	if (complete_command == NULL)
		return (-1);
	command = complete_command;
	while (command != NULL)
	{
		pipe_seq = command->pipe_sequence;
		while (pipe_seq != NULL)
		{
			if (process_simple_cmd(shell, env_list, pipe_seq->simple_command))
				return (-1);
			pipe_seq = pipe_seq->next;
		}
		command = command->next;
	}
	return (0);
}
