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

int		exec_complete_command(t_complete_cmd *complete_cmd, t_env *env_list)
{
	while (complete_cmd != NULL)
	{
		exec_pipe_sequence(complete_cmd->pipe_sequence, env_list);
		complete_cmd = complete_cmd->next;
	}
	return (0);
}
