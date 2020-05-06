/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_complete_command.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 15:46:44 by lgutter       #+#    #+#                 */
/*   Updated: 2020/04/28 15:46:44 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int		exec_complete_command(t_shell *shell, t_complete_cmd *complete_cmd,
								t_env *env_list)
{
	while (complete_cmd != NULL)
	{
		if (word_processing(shell, env_list, complete_cmd) != 0)
			return (-1);
		exec_pipe_sequence(complete_cmd->pipe_sequence, env_list);
		complete_cmd = complete_cmd->next;
	}
	return (0);
}
