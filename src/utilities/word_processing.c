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

static int		process_redirects(t_shell *shell, t_env *env_list,
								t_simple_cmd *simple_command)
{
	t_io_redirect	*redir;

	redir = simple_command->redirects;
	while (redir != NULL)
	{
		if (redir->io_number != NULL)
			redir->io_fd = ft_atoi(redir->io_number);
		if (redir->io_file != NULL && redir->io_file->filename != NULL)
		{
			if (process_word(shell, env_list, &(redir->io_file->filename), 'y'))
				return (-1);
		}
		if (redir->io_here != NULL && redir->io_here->here_end != NULL)
		{
			if (process_word(shell, env_list, &(redir->io_here->here_end), 'n'))
				return (-1);
			if (get_here_doc(redir->io_here, shell) != 0)
				return (malloc_error);
		}
		redir = redir->next;
	}
	return (0);
}

static size_t	arg_list_len(t_argument *list)
{
	size_t len;

	len = 0;
	while (list != NULL)
	{
		len++;
		list = list->next;
	}
	return (len);
}

static char		**convert_arguments(t_argument *args)
{
	char		**argv;
	size_t		count;

	count = arg_list_len(args);
	argv = (char **)ft_memalloc(sizeof(char *) * (count + 1));
	if (argv == NULL)
		return (handle_error_p(malloc_error, NULL));
	argv[count] = NULL;
	count = 0;
	while (args != NULL)
	{
		if (args->argument == NULL)
			return (handle_error_p(parsing_error, NULL));
		argv[count] = ft_strdup(args->argument);
		if (argv[count] == NULL)
		{
			free_dchar_arr(argv);
			return (handle_error_p(malloc_error, NULL));
		}
		count++;
		args = args->next;
	}
	return (argv);
}

static int		process_simple_cmd(t_shell *shell, t_env *env_list,
								t_simple_cmd *simple_command)
{
	t_argument		*cur_arg;

	if (process_redirects(shell, env_list, simple_command) != 0)
		return (-1);
	if (simple_command->arguments == NULL)
		return (handle_error_str(parsing_error, "no arguments"));
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
	simple_command->argv = convert_arguments(simple_command->arguments);
	return (0);
}

int				word_processing(t_shell *shell, t_env *env_list,
								t_complete_cmd *complete_command)
{
	t_pipe_sequence	*pipe_seq;

	if (complete_command == NULL)
		return (-1);
	pipe_seq = complete_command->pipe_sequence;
	while (pipe_seq != NULL)
	{
		if (process_simple_cmd(shell, env_list, pipe_seq->simple_command))
			return (-1);
		pipe_seq = pipe_seq->next;
	}
	return (0);
}
