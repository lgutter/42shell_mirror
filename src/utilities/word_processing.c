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

	if (simple_command == NULL)
		return (handle_error_str(parsing_error, "NULL simple command"));
	if (process_redirects(shell, env_list, simple_command->redirects) != 0)
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
	int				ret;

	if (complete_command == NULL)
		return (handle_error_str(parsing_error, "NULL complete command"));
	pipe_seq = complete_command->pipe_sequence;
	if (pipe_seq == NULL)
		return (handle_error_str(parsing_error, "NULL pipe sequence"));
	while (pipe_seq != NULL)
	{
		if (pipe_seq->pipe == pipe_op &&
			(pipe_seq->next == NULL || pipe_seq->next->simple_command == NULL ||
			pipe_seq->next->simple_command->arguments == NULL))
			return (handle_error_str(parsing_error, "incomplete pipe"));
		ret = process_simple_cmd(shell, env_list, pipe_seq->simple_command);
		if (ret != 0)
			return (ret);
		pipe_seq = pipe_seq->next;
	}
	return (0);
}
