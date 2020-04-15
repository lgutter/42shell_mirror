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
#include "utils.h"
#include "environment.h"

static int	process_word(t_env *env_list, char **word)
{
	int	quote_type;

	quote_type = check_quote(*word);
	if (quote_type < 0)
	{
		if (complete_quote(word) != 0)
			return (-1);
		quote_type = check_quote(*word);
	}
	if (quote_type == 0 || quote_type == 2)
	{
		if (expand_variable(env_list, word) != 0)
			return (-1);
	}
	if (quote_type > 0)
	{
		if (remove_quotes(word) != 0)
			return (-1);
	}
	return (0);
}

static int	words_simple_command(t_env *env_list, t_simple_cmd *simple_command)
{
	t_io_redirect	*redirect;
	t_argument		*argument;

	redirect = simple_command->redirects;
	while (redirect != NULL)
	{
		if (redirect->io_file != NULL && redirect->io_file->filename != NULL)
		{
			if (process_word(env_list, &(redirect->io_file->filename)) != 0)
				return (-1);
		}
		redirect = redirect->next;
	}
	argument = simple_command->arguments;
	while (argument != NULL)
	{
		if (argument->argument != NULL)
		{
			if (process_word(env_list, &(argument->argument)) != 0)
				return (-1);
		}
		argument = argument->next;
	}
	return (0);
}

int			word_processing(t_env *env_list, t_complete_cmd *complete_command)
{
	t_complete_cmd	*command;
	t_pipe_sequence	*pipe_seq;

	command = complete_command;
	while (command != NULL)
	{
		pipe_seq = command->pipe_sequence;
		while (pipe_seq != NULL)
		{
			if (words_simple_command(env_list, pipe_seq->simple_command) != 0)
				return (-1);
			pipe_seq = pipe_seq->next;
		}
		command = command->next;
	}
	return (0);
}
