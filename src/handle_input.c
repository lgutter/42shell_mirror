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

int		handle_input(t_shell *shell, char **buffer)
{
	t_token			*tokens;
	t_token			*tokens_start;
	t_complete_cmd	*complete_command;
	int				ret;

	if (buffer == NULL || *buffer == NULL)
		return (-1);
	ret = 0;
	tokens = tokenizer(shell, buffer);
	if (tokens != NULL)
	{
		tokens_start = tokens;
		complete_command = parse_complete_command(&tokens);
		if (complete_command != NULL)
		{
			ret = exec_complete_command(shell, complete_command);
			free_complete_command(complete_command);
			configure_terminal(shell, 2);
		}
		free_token_list(&tokens_start);
	}
	return (ret);
}
