/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_input.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:52:43 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/14 11:52:43 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_INPUT_H
# define HANDLE_INPUT_H
# include "tokenizer.h"
# include "parser.h"
# include "environment.h"

int		handle_input(char *buffer);

int		word_processing(t_env *env_list, t_complete_cmd *complete_command);
#endif
