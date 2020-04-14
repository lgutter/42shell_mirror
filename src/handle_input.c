/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_input.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 11:51:50 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/14 11:51:50 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "handle_input.h"
#include "TEMP_print_token_parse.h"

int		handle_input(const char *buffer)
{
	t_token			*tokens;
	t_token			*tokens_start;
	t_complete_cmd	*complete_command;

	if (buffer == NULL)
		return (-1);
	tokens = tokenizer(buffer);
	tokens_start = tokens;
	print_tokens(tokens);
	if (tokens != NULL)
	{
		complete_command = parse_complete_command(&tokens);
		if (complete_command != NULL)
			print_complete_command(complete_command);
		free_complete_command(complete_command);
	}
	free_token_list(&tokens_start);
	return (0);
}
