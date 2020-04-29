/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_structs.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/09 15:33:36 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/09 15:33:36 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_STRUCTS_H
# define PARSER_STRUCTS_H
# include "tokenizer.h"

/*
**	Enumeration to limit the possible values of the seperator operator
**	in the complete_cmd struct.
*/
typedef enum					e_seperator_op
{
	no_seperator_op = 0,
	background_op = AMP,
	semicolon_op = SEMI
}								t_seperator_op;

/*
**	Enumeration to limit the possible values of the pipe operator
**	in the pipe_sequence struct.
*/
typedef enum					e_pipe_op
{
	no_pipe = 0,
	pipe_op
}								t_pipe_op;

/*
**	Enumeration to limit the possible values of the redirection operator
**	in the io_redirect struct.
*/
typedef enum					e_redirect_op
{
	no_redirect_op = 0,
	redirect_in = LESS,
	redirect_out = GREAT,
	redirect_append = DGREAT,
	redirect_fd_in = LESSAMP,
	redirect_fd_out = GREATAMP
}								t_redirect_op;

/*
**	Struct to hold the first element in the complete_commands list.
*/
typedef struct					s_program
{
	struct s_complete_cmd		*complete_commands;
}								t_program;

/*
**	Struct for every node in the complete_commands list.
**	fields:
**	pipe_sequence:	first element in pipe_sequence list.
**	seperator_op:	an [optional] seperator op to seperate the command.
**	next:			the next node in the list.
*/
typedef struct					s_complete_cmd
{
	struct s_pipe_sequence		*pipe_sequence;
	t_seperator_op				seperator_op;
	struct s_complete_cmd		*next;
}								t_complete_cmd;

/*
**	Struct to hold the first element in the pipe_sequence list.
**	fields:
**	simple_command:	the simple_command struct.
**	pipe:			an [optional] pipe operator signifying another
**					command will follow that the output of this command
**					should be piped to.
**	next:			the next node in the list.
*/
typedef struct					s_pipe_sequence
{
	struct s_simple_command		*simple_command;
	t_pipe_op					pipe;
	struct s_pipe_sequence		*next;
}								t_pipe_sequence;

/*
**	Struct to hold the information for a simple command.
**	fields:
**	redirects:	[optional] list of all redirections to be performed for this
**				command. these will be performed in order, so redirections
**				to/from the same fd mean that only the last one is active.
**	arguments:	[optional] list of all arguments for the command, with the
**				first element always being the command name. (like argv[0])
*/
typedef struct					s_simple_command
{
	struct s_io_redirect		*redirects;
	struct s_argument			*arguments;
	char						**argv;
}								t_simple_cmd;

/*
**	Struct for every node in the arguments list.
**	fields:
**	argument:	the argument as a string.
**	next:		the next node in the list.
*/
typedef struct					s_argument
{
	char						*argument;
	struct s_argument			*next;
}								t_argument;

/*
**	Struct for every node in the redirections list.
**	it will always contain EITHER an io_file OR an io_here.
**	fields:
**	io_number:	an [optional] string containing the io number(fd).
**	io_file:	an [optional] io_file struct specifying a file(descriptor)
**				redirection.
**	io_here:	an [optional] io_here struct specifying a heredoc redirection.
**	next:		the next node in the list.
*/
typedef struct					s_io_redirect
{
	char						*io_number;
	int							io_fd;
	struct s_io_file			*io_file;
	struct s_io_here			*io_here;
	struct s_io_redirect		*next;

}								t_io_redirect;

/*
**	Struct to hold the information for a file redirection.
**	fields:
**	redirect_op:	the operator specifying the kind of redirection.
**	filename:		a string specifying the name of the file to redirect to,
**					or a file descriptor if the operator specifies an fd.
*/
typedef struct					s_io_file
{
	t_redirect_op				redirect_op;
	char						*filename;
}								t_io_file;

/*
**	Struct to hold the information for a heredoc redirection.
**	fields:
**	here_end:	string containing the word that is used to end the heredoc.
*/
typedef struct					s_io_here
{
	char						*here_end;
	char						*here_doc;
}								t_io_here;

#endif
