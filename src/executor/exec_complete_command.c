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
	int	ret;

	ret = 0;
	while (complete_cmd != NULL)
	{
		ret = word_processing(shell, env_list, complete_cmd);
		if (ret == 0)
			ret = exec_pipe_sequence(complete_cmd->pipe_sequence, env_list);
		complete_cmd = complete_cmd->next;
	}
	return (ret);
}
