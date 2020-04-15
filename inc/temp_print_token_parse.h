/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   temp_print_token_parse.h                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 12:00:33 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/14 12:00:33 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMP_PRINT_TOKEN_PARSE_H
# define TEMP_PRINT_TOKEN_PARSE_H
# include "tokenizer.h"
# include "parser.h"

void	print_arguments(t_argument *arguments);
void	print_io_redirect(t_io_redirect *io_redirect);
void	print_simple_command(t_simple_cmd *simple_command);
void	print_pipe_sequence(t_pipe_sequence *pipe_sequence);
void	print_complete_command(t_complete_cmd *complete_command);
void	print_tokens(t_token *tokens);

#endif
