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

void	print_complete_command(t_complete_cmd *complete_command);
void	print_tokens(t_token *tokens);

#endif
