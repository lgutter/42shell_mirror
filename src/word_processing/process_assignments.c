/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_assignments.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 15:02:39 by lgutter       #+#    #+#                 */
/*   Updated: 2020/07/28 15:02:39 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

void		restore_assignments(t_shell *shell, t_simple_cmd *simple_cmd)
{
	t_assignment	*assignment;
	int				opts;

	if (shell == NULL || simple_cmd == NULL || simple_cmd->argv == NULL)
		return ;
	opts = (ENV_VAR | FORCE_VAR);
	assignment = simple_cmd->assignments;
	while (assignment != NULL)
	{
		if (assignment->original == NULL)
			ft_unsetenv(shell->env, assignment->key, opts);
		else
			ft_setenv(shell->env, assignment->key, assignment->original, opts);
		assignment = assignment->next;
	}
}

static int	process_assignment(t_shell *shell, t_assignment *assignment,
																	int opts)
{
	char *temp;

	if (assignment->value != NULL)
	{
		if (process_word(shell, &(assignment->value), ALL_QUOTES_TABLE) != 0)
			return (-1);
	}
	temp = ft_getenv(shell->env, assignment->key, opts);
	assignment->original = temp;
	ft_setenv(shell->env, assignment->key, assignment->value, opts);
	return (0);
}

int			process_assignments(t_shell *shell, t_simple_cmd *simple_cmd)
{
	int				opts;
	t_assignment	*assignment;

	if (simple_cmd == NULL ||
		(simple_cmd->assignments != NULL && shell == NULL))
		return (-1);
	opts = SHELL_VAR;
	if (simple_cmd->arguments != NULL)
		opts = ENV_VAR;
	assignment = simple_cmd->assignments;
	while (assignment != NULL)
	{
		if (process_assignment(shell, assignment, opts) != 0)
			return (-1);
		assignment = assignment->next;
	}
	return (0);
}
