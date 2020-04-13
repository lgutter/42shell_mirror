/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/09 15:40:10 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/09 15:40:10 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "ft_printf.h"
# include "libft.h"
# include "handle_error.h"
# include "tokenizer.h"
# include "parser_utils.h"
# include "parser_structs.h"
# include <stdlib.h>

/*
**	parsing functions. Each of these functions is responsible of parsing
**	a specific element of the syntax tree, each of which is defined as a
**	struct in parser_structs.h
*/
t_complete_cmd	*parse_complete_command(t_token **token);
t_pipe_sequence	*parse_pipe_sequence(t_token **token);
t_simple_cmd	*parse_simple_command(t_token **token);
t_argument		*parse_arguments(t_token **token);
t_io_redirect	*parse_io_redirect(t_token **token);
t_io_here		*parse_io_here(t_token **token);
t_io_file		*parse_io_file(t_token **token);

/*
**	free functions for all the parser structs.
**	these functions call the needed free functions to free every element of
**	the struct they are supposed to free, sets all elements to NULL,
**	after which it frees the struct itself, and returns NULL.
*/

t_complete_cmd	*free_complete_command(t_complete_cmd *complete_cmd);
t_pipe_sequence	*free_pipe_sequence(t_pipe_sequence *pipe_sequence);
t_simple_cmd	*free_simple_command(t_simple_cmd *simple_command);
t_argument		*free_arguments(t_argument *arguments);
t_io_redirect	*free_io_redirect(t_io_redirect *io_redirect);
t_io_here		*free_io_here(t_io_here *io_here);
t_io_file		*free_io_file(t_io_file *io_file);

#endif
