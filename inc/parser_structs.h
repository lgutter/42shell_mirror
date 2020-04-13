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

typedef enum					e_seperator_op
{
	no_seperator_op = 0,
	background_op = AMP,
	semicolon_op = SEMI
}								t_seperator_op;

typedef enum					e_pipe_op
{
	no_pipe = 0,
	pipe_op
}								t_pipe_op;

typedef enum					e_redirect_op
{
	no_redirect_op = 0,
	redirect_in = LESS,
	redirect_out = GREAT,
	redirect_append = DGREAT,
	redirect_fd_in = LESSAMP,
	redirect_fd_out = GREATAMP
}								t_redirect_op;

typedef struct					s_program
{
	struct s_complete_cmd		*complete_commands;
}								t_program;

typedef struct					s_complete_cmd
{
	struct s_pipe_sequence		*pipe_sequence;
	t_seperator_op				seperator_op;
	struct s_complete_cmd		*next;
}								t_complete_cmd;

typedef struct					s_pipe_sequence
{
	struct s_simple_command		*simple_command;
	t_pipe_op					pipe;
	struct s_pipe_sequence		*next;
}								t_pipe_sequence;

typedef struct					s_simple_command
{
	struct s_io_redirect		*redirects;
	struct s_argument			*arguments;
}								t_simple_cmd;

typedef struct					s_argument
{
	char						*argument;
	struct s_argument			*next;
}								t_argument;

typedef struct					s_io_redirect
{
	char						*io_number;
	struct s_io_file			*io_file;
	struct s_io_here			*io_here;
	struct s_io_redirect		*next;

}								t_io_redirect;

typedef struct					s_io_file
{
	t_redirect_op				redirect_op;
	char						*filename;
}								t_io_file;

typedef struct					s_io_here
{
	char						*here_end;
}								t_io_here;

// newline_list	: newline_list NEWLINE
// 				;
// linebreak		: newline_list

#endif
