/* ************************************************************************** */
/*                                                                            */
/*   cetushell - 21 Shell                                 ::::::::            */
/*                                                      :+:    :+:            */
/*   By: dkroeke <dkroeke@student.codam.nl>            +:+                    */
/*       lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*                                                 #+#    #+#                 */
/*   License: GPLv3                                ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "ft_printf.h"
# include "libft.h"
# include "handle_error.h"
# include "tokenizer.h"
# include "parser_utils.h"
# include <stdlib.h>

typedef enum					e_seperator_op
{
	empty = 0,
	background = AMP,
	semicolon = SEMI
}								t_seperator_op;

typedef enum					e_pipe_op
{
	empty = 0,
	pipe
}								t_pipe_op;

typedef enum					e_redirect_op
{
	redirect_in = LESS,
	redirect_out = GREAT,
	redirect_append = DGREAT,
	redirect_fd_in = LESSAMP,
	redirect_fd_out = GREATAMP
}								t_redirect_op;

typedef struct					s_program
{
	struct s_program 			*program;
	struct s_complete_command	*complete_command;
}								t_program;

typedef struct					s_complete_command
{
	struct s_pipe_sequence		*pipe_sequence;
	t_seperator_op				seperator_op;
}								t_complete_command;

typedef struct					s_pipe_sequence
{
	struct s_pipe_sequence		*pipe_sequence;
	t_type						pipe;
	struct s_simple_command		*simple_command;
}								t_pipe_sequence;

typedef struct					s_simple_command
{
	struct s_cmd_prefix			*cmd_prefix;
	char						*cmd_word;
	struct s_cmd_suffix			*cmd_suffix;
}								t_simple_command;

typedef struct					s_cmd_prefix
{
	struct s_cmd_prefix			*cmd_prefix;
	struct s_io_redirect		*io_redirect;
}								t_cmd_prefix;

typedef struct					s_cmd_suffix
{
	struct s_cmd_suffix			*cmd_suffix;
	char						*word;
	struct s_io_redirect		*io_redirect;
}								t_cmd_suffix;

typedef struct					s_io_redirect
{
	struct s_cmd_suffix			*cmd_suffix;
	char						*io_number;
	struct s_io_file			*io_file;
	struct s_io_file			*io_here;
}								t_cmd_suffix;

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
