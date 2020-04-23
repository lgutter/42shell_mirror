/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_parse_testmain.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/09 13:10:30 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/09 13:10:30 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"
#include <stdio.h>

static const char *g_token_types[GREATAMP + 1] =
{
	[undetermined] = "undetermined",
	[WORD] = "WORD",
	[IO_NUMBER] = "IO_NUMBER",
	[NEWLINE] = "NEWLINE",
	[PIPE] = "PIPE",
	[SEMI] = "SEMI",
	[AMP] = "AMP",
	[LESS] = "LESS",
	[GREAT] = "GREAT",
	[DLESS] = "DLESS",
	[DGREAT] = "DGREAT",
	[LESSAMP] = "LESSAMP",
	[GREATAMP] = "GREATAMP"
};

static void print_arguments(t_argument *arguments)
{
	while (arguments != NULL)
	{
		printf("\t\t\t- %s\n", arguments->argument);
		arguments = arguments->next;
	}
}

static void	print_io_redirect(t_io_redirect *io_redirect)
{
	while (io_redirect != NULL)
	{
		if (io_redirect->io_number != NULL)
			ft_printf("\t\t\tio_number: %s\n", io_redirect->io_number);
		if (io_redirect->io_file != NULL)
			ft_printf("\t\t\tio_file: op: %s; filename: %s\n", g_token_types[io_redirect->io_file->redirect_op], io_redirect->io_file->filename);
		if (io_redirect->io_here != NULL)
			ft_printf("\t\t\tio_here: %s\n", io_redirect->io_here->here_end);
		io_redirect = io_redirect->next;
	}
	printf("\t\t\t--------\n");
}

static void	print_simple_command(t_simple_cmd *simple_command)
{
	if (simple_command->redirects != NULL)
	{
		printf("\t\tREDIRECTIONS:\n");
		print_io_redirect(simple_command->redirects);
	}
	if (simple_command->arguments != NULL)
	{
		printf("\t\tARGUMENTS:\n");
		print_arguments(simple_command->arguments);
	}
}

static void	print_pipe_sequence(t_pipe_sequence *pipe_sequence)
{
	int i;

	i = 1;
	while (pipe_sequence != NULL)
	{
		printf("\tPIPE SEQUENCE #%i:\n\t~~~~~~~~\n", i);
		print_simple_command(pipe_sequence->simple_command);
		if (pipe_sequence->pipe == pipe_op)
			printf("\t--- PIPE DETECTED ---\n");
		pipe_sequence = pipe_sequence->next;
		i++;
		printf("\t~~~~~~~~\n");
	}
}

static void	print_complete_command(t_complete_cmd *complete_command)
{
	int i;

	i = 1;
	while (complete_command != NULL)
	{
		printf("COMMAND #%i:\n==============================\n", i);
		print_pipe_sequence(complete_command->pipe_sequence);
		if (complete_command->seperator_op == semicolon_op)
			printf("== SEMICOLON ==\n");
		if (complete_command->seperator_op == background_op)
			printf("== BACKGROUND ==\n");
		complete_command = complete_command->next;
		i++;
		printf("==============================\n");
	}
}

static void	print_tokens(t_token *tokens)
{
	while (tokens != NULL)
	{
		ft_printf("token type: %s\n token value: [%s]\n\n", g_token_types[tokens->type], tokens->value);
		tokens = tokens->next;
	}
}

int	main(int argc, char **argv)
{
	t_token			*tokens;
	t_token			*tokens_start;
	t_complete_cmd	*complete_command;
	int				i;

	i = 1;
	if (argc < 2)
	{
		ft_printf("please provide strings to parse!\n");
		return (1);
	}
	while (i < argc)
	{
		ft_printf("---------------\nArgument #%i\n---------------\n", i);
		tokens = tokenizer(argv[i]);
		tokens_start = tokens;
		print_tokens(tokens);
		complete_command = parse_complete_command(&tokens);
		print_complete_command(complete_command);
		free_complete_command(complete_command);
		free_token_list(&tokens_start);
		tokens = NULL;
		i++;
	}
	return (0);
}
